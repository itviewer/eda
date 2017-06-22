#include "parteditor.h"
#include "partview.h"
#include "ui_parteditor.h"

#include "statemachine.h"

#include "settinggrid.h"
#include "settingcolor.h"
#include "settingfont.h"

#include "newpartdialog.h"

#include "db.h"

#include "partlibmanager.h"


PartEditor::PartEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PartEditor),
    currentStateAction(nullptr)
{
    ui->setupUi(this);
    partEditor = this;

    init();

    // 中间
    partView = new PartView;
    setCentralWidget(partView);

    connect(this,&PartEditor::launched,
            this,&PartEditor::postInit);
}

PartEditor::~PartEditor()
{
    delete ui;
}

PartScene *PartEditor::currentScene() const
{
    return partView->partScene;
}

void PartEditor::setSceneState(const FSM &state, QAction *action)
{
    if(action){
        if(currentStateAction == action){
            // 点自己
            currentStateAction->setChecked(false);
            currentStateAction = nullptr;
            emit sceneStateChanged(FSM::SelectState);
        }else{
            if (currentStateAction)
                currentStateAction->setChecked(false);
            currentStateAction = action;

            // 切换绘图状态
            emit sceneStateChanged(state);
        }
    }else{
        //可能由按键如ESC或程序触发 如切换视图
        if (currentStateAction)
            currentStateAction->setChecked(false);
        currentStateAction = actionButtonSelect;
        currentStateAction->setChecked(true);
        emit sceneStateChanged(FSM::SelectState);
    }
}

void PartEditor::closeEvent(QCloseEvent *event)
{

    QMainWindow::closeEvent(event);
}

void PartEditor::postInit()
{
    createMenuFile();
    createMenuEdit();
    createMenuView();
    createMenuTools();
    createMenuSetup();
    createMenuHelp();

    settingGrid = new SettingGrid;
    settingColor = new SettingColor;
    settingFont = new SettingFont;

    partLib = new Db(":memory:","partlib");
    partLib->load("H:/eda/sch.db");

    partLibManager = new PartLibManager;

}

void PartEditor::onActionNewTriggered()
{
    createNewPart();
}

void PartEditor::onActionZoomInTriggered()
{
    partView->zoomIn();
}

void PartEditor::onActionZoomOutTriggered()
{
    partView->zoomOut();
}

void PartEditor::onActionZoomOneTriggered()
{
    partView->zoomOne();
}

void PartEditor::init()
{
    undoStack = new QUndoStack(this);
    fsm = new StateMachine(this);
    connect(this,&PartEditor::sceneStateChanged,
            fsm,&StateMachine::onSceneStateChanged);

    createToolButtonMain();
    createToolButtonDrawing();

    schColor.background = "#408080";
    schColor.display = "#000000";
    schColor.selection = "#FF00FF";
    schColor.drawing = "#BF7F7F";
}

void PartEditor::createMenuFile()
{
    QAction *actionMenuNew = new QAction("新建元件",this);
    ui->menuFile->addAction(actionMenuNew);
    connect(actionMenuNew,&QAction::triggered,this,&PartEditor::onActionNewTriggered);

    QAction *actionMenuLibraryManager = new QAction("元件库",this);
    ui->menuFile->addAction(actionMenuLibraryManager);
    connect(actionMenuLibraryManager,&QAction::triggered,this,[this](){
        partLibManager->show();
    });
}

void PartEditor::createMenuEdit()
{
    QAction *actionMenuUndo = new QAction("Undo",this);
    ui->menuEdit->addAction(actionMenuUndo);

    QAction *actionMenuRedo = new QAction("Redo",this);
    ui->menuEdit->addAction(actionMenuRedo);

}

void PartEditor::createMenuView()
{
    QAction *actionMenuZoomIn = new QAction("放大",this);
    ui->menuView->addAction(actionMenuZoomIn);
    connect(actionMenuZoomIn,&QAction::triggered,this,&PartEditor::onActionZoomInTriggered);


    QAction *actionMenuZoomOut = new QAction("缩小",this);
    ui->menuView->addAction(actionMenuZoomOut);
    connect(actionMenuZoomOut,&QAction::triggered,this,&PartEditor::onActionZoomOutTriggered);

    QAction *actionMenuZoomOne = new QAction("重置",this);
    ui->menuView->addAction(actionMenuZoomOne);
    connect(actionMenuZoomOne,&QAction::triggered,this,&PartEditor::onActionZoomOneTriggered);

}

void PartEditor::createMenuTools()
{
    QAction *actionMenuFootprint = new QAction("封装编辑器",this);
    ui->menuTool->addAction(actionMenuFootprint);

}

void PartEditor::createMenuSetup()
{
    QAction *actionMenuFont = new QAction("字体",this);
    ui->menuSetup->addAction(actionMenuFont);
    connect(actionMenuFont,&QAction::triggered,this,[this](){
        settingFont->show();
    });

    QAction *actionMenuGrid = new QAction("栅格",this);
    ui->menuSetup->addAction(actionMenuGrid);
    connect(actionMenuGrid,&QAction::triggered,this,[this](){
        settingGrid->show();
    });

    QAction *actionMenuColor = new QAction("颜色",this);
    ui->menuSetup->addAction(actionMenuColor);
    connect(actionMenuColor,&QAction::triggered,this,[this](){
        settingColor->show();
    });
}

void PartEditor::createMenuHelp()
{
    QAction *actionMenuAbout = new QAction("关于",this);
    ui->menuHelp->addAction(actionMenuAbout);
}

void PartEditor::createToolButtonMain()
{
    // 创建主工具栏
    QAction *actionButtonNew = new QAction(QIcon(":/new.png"),"新建",this);
    ui->toolBarMain->addAction(actionButtonNew);
    connect(actionButtonNew,&QAction::triggered,this,&PartEditor::onActionNewTriggered);

    QAction *actionButtonOpen = new QAction(QIcon(":/open.png"),"打开",this);
    ui->toolBarMain->addAction(actionButtonOpen);
//    connect(actionButtonOpen,&QAction::triggered,this,&PartEditor::onActionOpenTriggered);

    QAction *actionButtonSave = new QAction(QIcon(":/save.png"),"保存",this);
    ui->toolBarMain->addAction(actionButtonSave);
//    connect(actionButtonSave,&QAction::triggered,this,&PartEditor::onActionSaveTriggered);

    ui->toolBarMain->addSeparator();

    actionButtonUndo = undoStack->createUndoAction(this);
    actionButtonUndo->setIcon(QIcon(":/undo.png"));
    ui->toolBarMain->addAction(actionButtonUndo);

    actionButtonRedo = undoStack->createRedoAction(this);
    actionButtonRedo->setIcon(QIcon(":/redo.png"));
    ui->toolBarMain->addAction(actionButtonRedo);

    ui->toolBarMain->addSeparator();

    QAction *actionButtonZoomIn = new QAction(QIcon(":/zoomIn.png"),"放大",this);
    ui->toolBarMain->addAction(actionButtonZoomIn);
    connect(actionButtonZoomIn,&QAction::triggered,this,&PartEditor::onActionZoomInTriggered);

    QAction *actionButtonZoomOut = new QAction(QIcon(":/zoomOut.png"),"缩小",this);
    ui->toolBarMain->addAction(actionButtonZoomOut);
    connect(actionButtonZoomOut,&QAction::triggered,this,&PartEditor::onActionZoomOutTriggered);

    QAction *actionButtonZoomOne = new QAction(QIcon(":/zoomOne.png"),"重置",this);
    ui->toolBarMain->addAction(actionButtonZoomOne);
    connect(actionButtonZoomOne,&QAction::triggered,this,&PartEditor::onActionZoomOneTriggered);


}

void PartEditor::createToolButtonDrawing()
{
    // 创建绘图工具栏
    actionButtonSelect = new QAction(QIcon(""),"选择",this);
    actionButtonSelect->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonSelect);
    connect(actionButtonSelect,&QAction::triggered,this, [this] () {
        setSceneState(FSM::SelectState,actionButtonSelect);
    });

    QAction *actionButtonLineItem = new QAction(QIcon(""),"直线",this);
    actionButtonLineItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonLineItem);
    connect(actionButtonLineItem,&QAction::triggered,this, [this,actionButtonLineItem] () {
        setSceneState(FSM::LineItemState,actionButtonLineItem);
    });

    QAction *actionButtonPolylineItem = new QAction(QIcon(""),"折线",this);
    actionButtonPolylineItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonPolylineItem);
    connect(actionButtonPolylineItem,&QAction::triggered,this, [this,actionButtonPolylineItem] () {
        setSceneState(FSM::PolylineItemState,actionButtonPolylineItem);
    });

    QAction *actionButtonRectItem = new QAction(QIcon(""),"矩形",this);
    actionButtonRectItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonRectItem);
    connect(actionButtonRectItem,&QAction::triggered,this, [this,actionButtonRectItem] () {
        setSceneState(FSM::RectItemState,actionButtonRectItem);
    });

    QAction *actionButtonRoundedRectItem = new QAction(QIcon(""),"圆角",this);
    actionButtonRoundedRectItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonRoundedRectItem);
    connect(actionButtonRoundedRectItem,&QAction::triggered,this, [this,actionButtonRoundedRectItem] () {
        setSceneState(FSM::RoundedRectItemState,actionButtonRoundedRectItem);
    });

    QAction *actionButtonPolygonItem = new QAction(QIcon(""),"多边",this);
    actionButtonPolygonItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonPolygonItem);
    connect(actionButtonPolygonItem,&QAction::triggered,this, [this,actionButtonPolygonItem] () {
        setSceneState(FSM::PolygonItemState,actionButtonPolygonItem);
    });

    QAction *actionButtonEllipseItem = new QAction(QIcon(""),"椭圆",this);
    actionButtonEllipseItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonEllipseItem);
    connect(actionButtonEllipseItem,&QAction::triggered,this, [this,actionButtonEllipseItem] () {
        setSceneState(FSM::EllipseItemState,actionButtonEllipseItem);
    });

    QAction *actionButtonArcItem = new QAction(QIcon(""),"弧形",this);
    actionButtonArcItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonArcItem);
    connect(actionButtonArcItem,&QAction::triggered,this, [this,actionButtonArcItem] () {
        setSceneState(FSM::ArcItemState,actionButtonArcItem);
    });

    QAction *actionButtonCubicBezierItem = new QAction(QIcon(""),"贝塞",this);
    actionButtonCubicBezierItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonCubicBezierItem);
    connect(actionButtonCubicBezierItem,&QAction::triggered,this, [this,actionButtonCubicBezierItem] () {
        setSceneState(FSM::CubicBezierItemState,actionButtonCubicBezierItem);
    });

    QAction *actionButtonTextItem = new QAction(QIcon(""),"文本",this);
    actionButtonTextItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonTextItem);
    connect(actionButtonTextItem,&QAction::triggered,this, [this,actionButtonTextItem] () {
        setSceneState(FSM::TextItemState,actionButtonTextItem);
    });

    ui->toolBarDrawing->addSeparator();

    QAction *actionButtonPinItem = new QAction(QIcon(""),"管脚",this);
    actionButtonPinItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonPinItem);
}

void PartEditor::createStatusLabel()
{

}

void PartEditor::createNewPart()
{
    NewPartDialog newPartDialog;
    newPartDialog.exec();

    if(newPartDialog.result()){

    }
}
