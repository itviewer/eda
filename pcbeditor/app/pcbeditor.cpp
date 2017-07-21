#include "pcbeditor.h"
#include "ui_pcbeditor.h"

#include "pcbview.h"
#include "pcbscene.h"

#include <QFileDialog>
#include <QMessageBox>

#include "globalsetting.h"

#include "dockwidget.h"
#include "dockwidgettoolbar.h"
#include "navigator.h"

#include "statemachine.h"
#include "setting.h"

PCBEditor::PCBEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PCBEditor),
    currentStateAction(nullptr)
{
    ui->setupUi(this);
    pcbEditor = this;

    setDockOptions( AnimatedDocks | AllowTabbedDocks | GroupedDragging | ForceTabbedDocks);

    init();

    navigatorDock = new DockWidget(tr("项目浏览器"),this);
    connect(navigatorDock,&DockWidget::autoHideButtonClicked,
            this,&PCBEditor::onDockAutoHideButtonClicked);

    navigator = new Navigator;
    navigatorDock->setWidget(navigator);
    addDockWidget(Qt::LeftDockWidgetArea,navigatorDock);

    createStatusLabel();

    pcbView = new PCBView;
    setCentralWidget(pcbView);

    connect(this,&PCBEditor::launch,
            this,&PCBEditor::postInit);

    setWindowTitle("IdeaEDA-iPCB");
}

PCBEditor::~PCBEditor()
{
    delete globalSetting;
    delete ui;
}

PCBScene *PCBEditor::pcbScene() const
{
    return pcbView->pcbScene;
}

void PCBEditor::addDockWidgetToolBar(Qt::DockWidgetArea area, DockWidgetToolBar *toolbar)
{
    dockToolBars.insert(area,toolbar);
    addToolBar(dockAreaToToolBarArea(area),toolbar);
}


DockWidgetToolBar *PCBEditor::getDockWidgetToolBar(Qt::DockWidgetArea area)
{
    return dockToolBars.value(area);
}

void PCBEditor::setSelectStatus(const QString &text)
{

}

void PCBEditor::setScaleStatus(const QString &text)
{

}

void PCBEditor::setPosStatus(const QPointF &pos)
{

}

void PCBEditor::setSceneState(const FSM &state, QAction *action)
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
        currentStateAction = actionSelect;
        currentStateAction->setChecked(true);
        emit sceneStateChanged(FSM::SelectState);
    }
}

void PCBEditor::closeEvent(QCloseEvent *event)
{
    bool needSave = false;


    QMainWindow::closeEvent(event);
}

void PCBEditor::postInit()
{
    setSceneState(FSM::SelectState);

    globalSetting = new GlobalSetting;

    fsm = new StateMachine(this);
    connect(this,&PCBEditor::sceneStateChanged,
            fsm,&StateMachine::onSceneStateChanged);
    pcbView->pcbScene->installEventFilter(fsm);

    createMenuSetting();
}

void PCBEditor::onMetadataSaved()
{

}

void PCBEditor::onDockAutoHideButtonClicked(bool autoHide)
{
    DockWidget *dockWidget = qobject_cast<DockWidget *>(sender());
    Qt::DockWidgetArea dockArea = dockWidgetArea(dockWidget);

    DockWidgetToolBar *dockToolBar = getDockWidgetToolBar(dockArea);
    if(autoHide){
        if(dockToolBar){
            dockToolBar->addDockWidget(dockWidget);
            addDockWidgetToolBar(dockArea,dockToolBar);
            dockToolBar->show();
        }else{
            dockToolBar = new DockWidgetToolBar(areaToOrientation(dockArea));
            dockToolBar->addDockWidget(dockWidget);
            addDockWidgetToolBar(dockArea,dockToolBar);
        }
        dockWidget->hide();
    }else{
        dockToolBar->removeDockWidget(dockWidget);
        dockToolBar->hide();
    }
}

void PCBEditor::init()
{
    undoGroup = new QUndoGroup(this);


    createToolButtonMain();
    createToolButtonDrawing();

    new Setting(this);
}

void PCBEditor::createMenuFile()
{

}

void PCBEditor::createMenuSetting()
{
    QAction *actionGlobalSetting = new QAction(tr("全局设置"),this);
    ui->menuSetting->addAction(actionGlobalSetting);
    connect(actionGlobalSetting,&QAction::triggered,this,[=](){
        globalSetting->show();
    });
}

void PCBEditor::createToolButtonMain()
{
    // 创建主工具栏
    QAction *actionOpen = new QAction(QIcon(":/icon/open.png"),tr("打开"),this);
    ui->toolBarMain->addAction(actionOpen);
    connect(actionOpen,&QAction::triggered,this,[=](){
        const QString filename = QFileDialog::getOpenFileName(this, tr("打开PCB文件"),
                                                              "H:/eda/eda/ePCB/test",
                                                              tr("PCB文件 (*.json *.pcb)"));
//        if(!filename.isEmpty()){
//            initSchematic(filename);
//        }
    });

    QAction *actionSave = new QAction(QIcon(":/icon/save.png"),tr("保存"),this);
    ui->toolBarMain->addAction(actionSave);
    connect(actionSave,&QAction::triggered,this,[=](){
        // 在页面中判断是否真需要保存
    });

    ui->toolBarMain->addSeparator();

    actionUndo = undoGroup->createUndoAction(this);
    actionUndo->setIcon(QIcon(":/icon/undo.png"));
    ui->toolBarMain->addAction(actionUndo);

    actionRedo = undoGroup->createRedoAction(this);
    actionRedo->setIcon(QIcon(":/icon/redo.png"));
    ui->toolBarMain->addAction(actionRedo);

    ui->toolBarMain->addSeparator();

    QAction *actionHome = new QAction(QIcon(":/icon/zoomAll.png"),tr("图页"),this);
    ui->toolBarMain->addAction(actionHome);

    QAction *actionZoomIn = new QAction(QIcon(":/icon/zoomIn.png"),tr("放大"),this);
    ui->toolBarMain->addAction(actionZoomIn);

    QAction *actionZoomOut = new QAction(QIcon(":/icon/zoomOut.png"),tr("缩小"),this);
    ui->toolBarMain->addAction(actionZoomOut);

    QAction *actionRoute = new QAction(QIcon(":/icon/route.png"),tr("交互布线"),this);
    ui->toolBarRoute->addAction(actionRoute);


    QAction *actionAutoRoute = new QAction(QIcon(":/icon/autoRoute.png"),tr("自动布线"),this);
    ui->toolBarRoute->addAction(actionAutoRoute);

}

void PCBEditor::createToolButtonDrawing()
{
    QAction *actionCopperPourItem = new QAction(QIcon(":/icon/copperPour.png"),tr("铜箔"),this);
    actionCopperPourItem->setCheckable(true);
    ui->toolBarDesign->addAction(actionCopperPourItem);

    QAction *actionMountingHoleItem = new QAction(QIcon(":/icon/hole.png"),tr("安装孔"),this);
    actionMountingHoleItem->setCheckable(true);
    ui->toolBarDesign->addAction(actionMountingHoleItem);

    QAction *actionBoardItem = new QAction(QIcon(""),tr("板框"),this);
    actionBoardItem->setCheckable(true);
    ui->toolBarDesign->addAction(actionBoardItem);

    // 创建绘图工具栏
    actionSelect = new QAction(QIcon(""),tr("选择"),this);
    actionSelect->setCheckable(true);
    ui->toolBarDrawing->addAction(actionSelect);
    connect(actionSelect,&QAction::triggered,this, [=] () {
        setSceneState(FSM::SelectState,actionSelect);
    });

    QAction *actionLineItem = new QAction(QIcon(""),tr("直线"),this);
    actionLineItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionLineItem);
    connect(actionLineItem,&QAction::triggered,this, [=] () {
        setSceneState(FSM::LineItemState,actionLineItem);
    });

    QAction *actionPolylineItem = new QAction(QIcon(""),tr("折线"),this);
    actionPolylineItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionPolylineItem);
    connect(actionPolylineItem,&QAction::triggered,this, [=] () {
        setSceneState(FSM::PolylineItemState,actionPolylineItem);
    });

    QAction *actionRectItem = new QAction(QIcon(""),tr("矩形"),this);
    actionRectItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionRectItem);
    connect(actionRectItem,&QAction::triggered,this, [=] () {
        setSceneState(FSM::RectItemState,actionRectItem);
    });

    QAction *actionRoundedRectItem = new QAction(QIcon(""),tr("圆角"),this);
    actionRoundedRectItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionRoundedRectItem);
    connect(actionRoundedRectItem,&QAction::triggered,this, [=] () {
        setSceneState(FSM::RoundedRectItemState,actionRoundedRectItem);
    });

    QAction *actionPolygonItem = new QAction(QIcon(""),tr("多边"),this);
    actionPolygonItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionPolygonItem);
    connect(actionPolygonItem,&QAction::triggered,this, [=] () {
        setSceneState(FSM::PolygonItemState,actionPolygonItem);
    });

    QAction *actionEllipseItem = new QAction(QIcon(""),tr("椭圆"),this);
    actionEllipseItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionEllipseItem);
    connect(actionEllipseItem,&QAction::triggered,this, [=] () {
        setSceneState(FSM::EllipseItemState,actionEllipseItem);
    });

    QAction *actionArcItem = new QAction(QIcon(""),tr("弧形"),this);
    actionArcItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionArcItem);
    connect(actionArcItem,&QAction::triggered,this, [=] () {
        setSceneState(FSM::ArcItemState,actionArcItem);
    });

    QAction *actionCubicBezierItem = new QAction(QIcon(""),tr("贝塞"),this);
    actionCubicBezierItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionCubicBezierItem);
    connect(actionCubicBezierItem,&QAction::triggered,this, [=] () {
        setSceneState(FSM::CubicBezierItemState,actionCubicBezierItem);
    });

    QAction *actionPixmapItem = new QAction(QIcon(""),tr("图片"),this);
    actionPixmapItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionPixmapItem);
    connect(actionPixmapItem,&QAction::triggered,this, [=] () {
        setSceneState(FSM::PixmapItemState,actionPixmapItem);
    });

    QAction *actionTextItem = new QAction(QIcon(""),tr("文本"),this);
    actionTextItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionTextItem);
    connect(actionTextItem,&QAction::triggered,this, [=] () {
        setSceneState(FSM::TextItemState,actionTextItem);
    });
}

void PCBEditor::createStatusLabel()
{

}
