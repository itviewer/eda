#include "schematiceditor.h"
#include "schematicview.h"
#include "schematicscene.h"
#include "tabcontainer.h"
#include "schematicio.h"
#include "settingio.h"
#include "defaultproperty.h"

#include "ui_schematiceditor.h"
#include "globalsetting.h"
#include "globalsettingcolorscheme.h"

#include "dockwidget.h"
#include "dockwidgettoolbar.h"

#include "partselector.h"
#include "partlibmanager.h"

#include "statemachine.h"

#include "newpagedialog.h"

#include <QMessageBox>

#include "navigator.h"
#include <QtConcurrent>
#include <QFutureWatcher>

#include "../parteditor/app/parteditor.h"

static bool savePageMetadata(SchematicScene *page)
{
    return page->saveMetaData();
}

SchematicEditor::SchematicEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SchematicEditor),
    currentStateAction(nullptr),
    currentSchView(nullptr)
{
    ui->setupUi(this);
    schEditor = this;

    setDockOptions( AnimatedDocks | AllowTabbedDocks | GroupedDragging | ForceTabbedDocks);

    // 构造函数仅保留和初始化UI相关和必要的初始化操作
    // 其它非必要操作在 postInit 中待主窗口显示后执行
    init();

    // 中间
    tabContainer = new TabContainer;
    setCentralWidget(tabContainer);

    // 左侧
    navigatorDock = new DockWidget("项目浏览器",this);
    connect(navigatorDock,&DockWidget::autoHideButtonClicked,
            this,&SchematicEditor::onDockAutoHideButtonClicked);

    navigator = new Navigator;
    navigatorDock->setWidget(navigator);
    addDockWidget(Qt::LeftDockWidgetArea,navigatorDock);

    // 右侧
    partSelector = new PartSelector("元件库");
    addDockWidget(Qt::RightDockWidgetArea,partSelector);

    // 底部
    createStatusLabel();


//    QUndoView *undoView = new QUndoView(undoGroup);
//    undoView->setWindowTitle("undo redo commands");
//    undoView->show();

    connect(this,&SchematicEditor::launched,
            this,&SchematicEditor::postInit);


    initSchematic();
    navigator->createNavigator();

    createNewSchPage();

    setWindowTitle("IdeaEDA-iCAD-未命名原理图");
}

SchematicEditor::~SchematicEditor()
{
    // 仅需要手动删除不是editor子对象的指针
    delete globalSetting;
    delete globalSettingColorScheme;
    delete partLibManager;
    delete ui;

    delete partEditor;
}

SchematicScene *SchematicEditor::currentScene() const
{
    return currentSchView->schScene;
}

void SchematicEditor::postInit()
{
    globalSetting = new GlobalSetting;
    globalSettingColorScheme = new GlobalSettingColorScheme;
    globalSettingColorScheme->setWindowModality(Qt::ApplicationModal);

    createMenuFile();
    createMenuEdit();
    createMenuView();
    createMenuTools();
    createMenuSetup();
    createMenuHelp();

    partLibManager = new PartLibManager;
    connect(partLibManager,&PartLibManager::partLibraryChanged,
            partSelector,&PartSelector::onPartLibraryChanged);

    setCorner(Qt::BottomLeftCorner,Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner,Qt::RightDockWidgetArea);

    connect(&schSaveWatcher,&QFutureWatcher<void>::finished,
            this,&SchematicEditor::onMetadataSaved);

    partEditor = new PartEditor;
    // TODO 是否有必要在PartEditor中反向包含SchematicEditor以便直接调用
    connect(partEditor,&PartEditor::aboutToQuit,this,&SchematicEditor::show);
}

void SchematicEditor::onMetadataSaved()
{
    if(schIO->saveSchematic()){
        // needSavedPage 会被filter自动过滤 只有向真需要保存的页面发射信号
        for(SchematicScene *page:needSavedPage){
            emit page->editingModeChanged(false);
        }
    }
    // 成功保存后清除待保存页面
    needSavedPage.clear();
}

void SchematicEditor::onDockAutoHideButtonClicked(bool autoHide)
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

void SchematicEditor::onActionNewTriggered()
{
    createNewSchPage(true);
}

void SchematicEditor::onActionOpenTriggered()
{
    const QString filename = QFileDialog::getOpenFileName(this, "打开原理图",
                                                          "H:/eda/eda/specification",
                                                          "原理图文件 (*.json *.sch)");
    if(!filename.isEmpty()){
        initSchematic(filename);
    }
}

void SchematicEditor::onActionSaveTriggered()
{
    // 在页面中判断是否真需要保存
    needSavedPage.append(currentSchView->schScene);
    schSaveFuture = QtConcurrent::filter(needSavedPage,savePageMetadata);
    schSaveWatcher.setFuture(schSaveFuture);
}

void SchematicEditor::onActionSaveAllTriggered()
{
    needSavedPage = tabContainer->openedSchPage();
    // needSavedPage 会被filter自动过滤
    schSaveFuture = QtConcurrent::filter(needSavedPage,savePageMetadata);
    schSaveWatcher.setFuture(schSaveFuture);
}

void SchematicEditor::onActionSaveAsTriggered()
{

}

void SchematicEditor::onActionCloseTriggered()
{
    bool needSave = false;
//    for(SchematicScene *page:tabContainer->openedSchPage()){
//        if(page->editingMode){
//            needSave = true;
//            break;
//        }
//    }
//    if(needSave){
//        int ret = QMessageBox::critical(this, "提示",
//                                        "尚有原理图页未保存\n"
//                                           "是否保存原理图？",
//                                        QMessageBox::Ok | QMessageBox::Cancel,
//                                        QMessageBox::Ok);

//        if(ret == QMessageBox::Ok){
//            // 任务栏图标已被隐藏
//            hide();
//            needSavedPage = tabContainer->openedSchPage();
//            // 如果使用filter则需要重置schSaveWatcher的连接
//            QtConcurrent::blockingFilter(needSavedPage,savePageMetadata);

//            schIO->saveSchematic();
//        }
    //    }
}

void SchematicEditor::onActionZoomInTriggered()
{
    currentSchView->zoomIn();
}

void SchematicEditor::onActionZoomOutTriggered()
{
    currentSchView->zoomOut();
}

void SchematicEditor::onActionZoomOneTriggered()
{
    currentSchView->zoomOne();
}

void SchematicEditor::onActionZoomHomeTriggered()
{
    currentSchView->zoomHome();
}

void SchematicEditor::onActionPartEditorTriggered()
{
    // 先隐藏SchematicEditor再显示partEditor有可能因程序先失去焦点变为非活动程序
    partEditor->show();
    hide();
}

void SchematicEditor::addDockWidgetToolBar(Qt::DockWidgetArea area, DockWidgetToolBar *toolbar)
{
    dockToolBars.insert(area,toolbar);
    addToolBar(dockAreaToToolBarArea(area),toolbar);
}

DockWidgetToolBar *SchematicEditor::getDockWidgetToolBar(Qt::DockWidgetArea area)
{
    return dockToolBars.value(area);
}

void SchematicEditor::setScaleStatus(const QString &text)
{
    labelScale->setText(text);
}

void SchematicEditor::setPosStatus(const QPointF &pos)
{
    labelPosX->setText(QString("%1").arg(pos.x() * milPerUnit,0,'f',0));
    labelPosY->setText(QString("%1").arg(pos.y() * milPerUnit,0,'f',0));
}

void SchematicEditor::setSceneState(const FSM &state, QAction *action)
{
    if(state == FSM::PartItemState){
        emit sceneStateChanged(FSM::PartItemState);
    }else{
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
}

void SchematicEditor::setFocusOfCurrentView()
{
    currentSchView->setFocus();
}

void SchematicEditor::onCurrentViewChanged(const int &index)
{
    if (tabContainer->count() && tabContainer->currentWidget()->inherits("SchematicView"))
    {
        // 仅通知当前场景
        disconnect(this,&SchematicEditor::sceneStateChanged,
                currentSchView->schScene,&SchematicScene::onSceneStateChanged);

        currentSchView = qobject_cast<SchematicView*>(tabContainer->currentWidget());

        connect(this,&SchematicEditor::sceneStateChanged,
                currentSchView->schScene,&SchematicScene::onSceneStateChanged);

        // 新开启或切换到原理图页 默认为选择态
        setSceneState(FSM::SelectState);
        currentSchView->schScene->onSelectionChanged();

        // 切换undo/redo 栈
        undoGroup->setActiveStack(currentSchView->schScene->undoStack);

        currentSchView->setFocus();

        resetStatusBar();
    }else{
        ui->toolBarDrawing->setDisabled(true);
    }
}

void SchematicEditor::onPartSelectChanged()
{
    setSceneState(FSM::PartItemState,actionButtonPartItem);
    actionButtonPartItem->setCheckable(true);
    actionButtonPartItem->setChecked(true);
}

void SchematicEditor::closeEvent(QCloseEvent *event)
{
    onActionCloseTriggered();
    QMainWindow::closeEvent(event);
}

void SchematicEditor::init()
{
    schIO = new SchematicIO(this);

    undoGroup = new QUndoGroup(this);
    fsm = new StateMachine(this);
    connect(this,&SchematicEditor::sceneStateChanged,
            fsm,&StateMachine::onSceneStateChanged);

    createToolButtonMain();
    createToolButtonWiring();
    createToolButtonDrawing();

    settingIO = new SettingIO(this);
}

void SchematicEditor::createMenuFile()
{
    QAction *actionMenuNew = new QAction("新建",this);
    ui->menuFile->addAction(actionMenuNew);
    connect(actionMenuNew,&QAction::triggered,this,&SchematicEditor::onActionNewTriggered);

    QAction *actionMenuOpen = new QAction("打开",this);
    ui->menuFile->addAction(actionMenuOpen);
    connect(actionMenuOpen,&QAction::triggered,this,&SchematicEditor::onActionOpenTriggered);

    QAction *actionMenuClose = new QAction("关闭",this);
    ui->menuFile->addAction(actionMenuClose);
    connect(actionMenuClose,&QAction::triggered,this,&SchematicEditor::onActionCloseTriggered);

    ui->menuFile->addSeparator();

    QAction *actionMenuSaveAll = new QAction("保存",this);
    ui->menuFile->addAction(actionMenuSaveAll);
    connect(actionMenuSaveAll,&QAction::triggered,this,&SchematicEditor::onActionSaveAllTriggered);

    QAction *actionMenuSaveAs = new QAction("另存为",this);
    ui->menuFile->addAction(actionMenuSaveAs);
    connect(actionMenuSaveAs,&QAction::triggered,this,&SchematicEditor::onActionSaveAsTriggered);

    QMenu *menuImport = new QMenu("导入",this);

//    QAction *actionMenuImportPads = new QAction("PADS Logic ASCII 9.0",this);
//    menuImport->addAction(actionMenuImportPads);

    ui->menuFile->addMenu(menuImport);

    QMenu *menuExport = new QMenu("导出",this);
//    QAction *actionMenuExportPads = new QAction("PADS Logic ASCII 9.0",this);
//    menuExport->addAction(actionMenuExportPads);


    ui->menuFile->addMenu(menuExport);

    QAction *actionMenuPDF = new QAction("智能PDF",this);
    ui->menuFile->addAction(actionMenuPDF);
//    connect(actionMenuPDF,&QAction::triggered,this,&SchematicEditor::onActionSaveAsTriggered);

    ui->menuFile->addSeparator();


    QAction *actionMenuLibraryManager = new QAction("元件库",this);
    ui->menuFile->addAction(actionMenuLibraryManager);
    connect(actionMenuLibraryManager,&QAction::triggered,this,[this](){
        partLibManager->show();
    });
}

void SchematicEditor::createMenuEdit()
{
    QAction *actionMenuUndo = new QAction("Undo",this);
    ui->menuEdit->addAction(actionMenuUndo);

    QAction *actionMenuRedo = new QAction("Redo",this);
    ui->menuEdit->addAction(actionMenuRedo);


}

void SchematicEditor::createMenuView()
{
    QAction *actionMenuZoomIn = new QAction("放大",this);
    ui->menuView->addAction(actionMenuZoomIn);
    connect(actionMenuZoomIn,&QAction::triggered,this,&SchematicEditor::onActionZoomInTriggered);


    QAction *actionMenuZoomOut = new QAction("缩小",this);
    ui->menuView->addAction(actionMenuZoomOut);
    connect(actionMenuZoomOut,&QAction::triggered,this,&SchematicEditor::onActionZoomOutTriggered);

    QAction *actionMenuZoomOne = new QAction("重置",this);
    ui->menuView->addAction(actionMenuZoomOne);
    connect(actionMenuZoomOne,&QAction::triggered,this,&SchematicEditor::onActionZoomOneTriggered);


    QAction *actionMenuZoomHome = new QAction("全局",this);
    ui->menuView->addAction(actionMenuZoomHome);
    connect(actionMenuZoomHome,&QAction::triggered,this,&SchematicEditor::onActionZoomHomeTriggered);
}

void SchematicEditor::createMenuTools()
{
    QAction *actionMenuPartEditor = new QAction("元件编辑器",this);
    ui->menuTools->addAction(actionMenuPartEditor);
    connect(actionMenuPartEditor,&QAction::triggered,this,&SchematicEditor::onActionPartEditorTriggered);
}

void SchematicEditor::createMenuSetup()
{
    QAction *actionMenuGlobalSetting = new QAction("全局设置",this);
    ui->menuSetup->addAction(actionMenuGlobalSetting);
    connect(actionMenuGlobalSetting,&QAction::triggered,this,[this](){
        globalSetting->show();
    });

    QAction *actionMenuSchematicSetting = new QAction("当前原理图",this);
    ui->menuSetup->addAction(actionMenuSchematicSetting);

    QAction *actionMenuPageSetting = new QAction("当前图页",this);
    ui->menuSetup->addAction(actionMenuPageSetting);

    ui->menuSetup->addSeparator();

    QAction *actionMenuGrid = new QAction("栅格设置",this);
    ui->menuSetup->addAction(actionMenuGrid);

    QAction *actionMenuColorScheme = new QAction("颜色设置",this);
    ui->menuSetup->addAction(actionMenuColorScheme);
    connect(actionMenuColorScheme,&QAction::triggered,globalSettingColorScheme,&GlobalSettingColorScheme::show);
}

void SchematicEditor::createMenuHelp()
{
    QAction *actionMenuSystemInfo = new QAction("系统信息",this);
    ui->menuHelp->addAction(actionMenuSystemInfo);

    ui->menuHelp->addSeparator();

    QAction *actionMenuAbout = new QAction("关于",this);
    ui->menuHelp->addAction(actionMenuAbout);
}

void SchematicEditor::createToolButtonMain()
{
    // 创建主工具栏
    // TODO 研究下 QStringLiteral 另外研究下5.10的QStringView
    QAction *actionButtonNew = new QAction(QIcon(":/icon/new.png"),"新建",this);
    ui->toolBarMain->addAction(actionButtonNew);
    connect(actionButtonNew,&QAction::triggered,this,&SchematicEditor::onActionNewTriggered);

    QAction *actionButtonOpen = new QAction(QIcon(":/icon/open.png"),"打开",this);
    ui->toolBarMain->addAction(actionButtonOpen);
    connect(actionButtonOpen,&QAction::triggered,this,&SchematicEditor::onActionOpenTriggered);

    QAction *actionButtonSave = new QAction(QIcon(":/icon/save.png"),"保存",this);
    ui->toolBarMain->addAction(actionButtonSave);
    connect(actionButtonSave,&QAction::triggered,this,&SchematicEditor::onActionSaveTriggered);


//    QAction *actionPrintPDF = new QAction(QIcon(""),"PDF"),this);
//    actionPrintPDF->setToolTip("PDF"));
//    ui->toolBarMain->addAction(actionPrintPDF);

    ui->toolBarMain->addSeparator();

    actionButtonCut = new QAction(QIcon(":/icon/cut.png"),"剪切",this);
    actionButtonCut->setDisabled(true);
    ui->toolBarMain->addAction(actionButtonCut);

    actionButtonCopy = new QAction(QIcon(":/icon/copy.png"),"复制",this);
    actionButtonCopy->setDisabled(true);
    ui->toolBarMain->addAction(actionButtonCopy);

    QAction *actionButtonPaste = new QAction(QIcon(":/icon/paste.png"),"粘贴",this);
    actionButtonPaste->setDisabled(true);
    ui->toolBarMain->addAction(actionButtonPaste);

    ui->toolBarMain->addSeparator();

    actionButtonUndo = undoGroup->createUndoAction(this);
    actionButtonUndo->setIcon(QIcon(":/icon/undo.png"));
    ui->toolBarMain->addAction(actionButtonUndo);

    actionButtonRedo = undoGroup->createRedoAction(this);
    actionButtonRedo->setIcon(QIcon(":/icon/redo.png"));
    ui->toolBarMain->addAction(actionButtonRedo);

    ui->toolBarMain->addSeparator();

    QAction *actionButtonZoomIn = new QAction(QIcon(":/icon/zoomIn.png"),"放大",this);
    ui->toolBarMain->addAction(actionButtonZoomIn);
    connect(actionButtonZoomIn,&QAction::triggered,this,&SchematicEditor::onActionZoomInTriggered);

    QAction *actionButtonZoomOut = new QAction(QIcon(":/icon/zoomOut.png"),"缩小",this);
    ui->toolBarMain->addAction(actionButtonZoomOut);
    connect(actionButtonZoomOut,&QAction::triggered,this,&SchematicEditor::onActionZoomOutTriggered);

    QAction *actionButtonZoomOne = new QAction(QIcon(":/icon/zoomOne.png"),"重置",this);
    ui->toolBarMain->addAction(actionButtonZoomOne);
    connect(actionButtonZoomOne,&QAction::triggered,this,&SchematicEditor::onActionZoomOneTriggered);

    QAction *actionButtonZoomHome = new QAction(QIcon(":/icon/zoomAll.png"),"全局",this);
    ui->toolBarMain->addAction(actionButtonZoomHome);
    connect(actionButtonZoomHome,&QAction::triggered,this,&SchematicEditor::onActionZoomHomeTriggered);


    QAction *actionButtonAnnotate = new QAction(QIcon(":/icon/annotation.png"),"排序",this);
    ui->toolBarDesign->addAction(actionButtonAnnotate);

    QAction *actionButtonDRCCheck = new QAction(QIcon(":/icon/drc.png"),"DRC",this);
    ui->toolBarDesign->addAction(actionButtonDRCCheck);

    QAction *actionButtonNetlist = new QAction(QIcon(":/icon/netlist.png"),"网表",this);
    ui->toolBarDesign->addAction(actionButtonNetlist);

    QAction *actionButtonBOM = new QAction(QIcon(":/icon/bom.png"),"BOM",this);
    ui->toolBarDesign->addAction(actionButtonBOM);

    ui->toolBarDesign->addSeparator();

    actionButtonSnapToGrid = new QAction(QIcon(":/icon/grid.png"),"栅格对齐",this);
    actionButtonSnapToGrid->setCheckable(true);
    actionButtonSnapToGrid->setChecked(true);
    ui->toolBarDesign->addAction(actionButtonSnapToGrid);
    connect(actionButtonSnapToGrid,&QAction::triggered,this, [this] (bool checked) {
        snapToGrid = checked;
    });


    QAction *actionButtonPCB = new QAction(QIcon(":/icon/pcb.png"),"同步PCB",this);
    ui->toolBarDesign->addAction(actionButtonPCB);

    QLineEdit *searchBox = new QLineEdit;
    searchBox->setFixedWidth(200);
    ui->toolBarSearchFilter->addWidget(searchBox);

    QAction *actionButtonSearch = new QAction(QIcon(":/icon/search.png"),"搜索",this);
    ui->toolBarSearchFilter->addAction(actionButtonSearch);

    QAction *actionButtonFilter = new QAction(QIcon(":/icon/filter.png"),"选择过滤",this);
    ui->toolBarSearchFilter->addAction(actionButtonFilter);
}

void SchematicEditor::createToolButtonDrawing()
{
    // 创建绘图工具栏
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

    QAction *actionButtonPixmapItem = new QAction(QIcon(""),"图片",this);
    actionButtonPixmapItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonPixmapItem);
    connect(actionButtonPixmapItem,&QAction::triggered,this, [this,actionButtonPixmapItem] () {
        setSceneState(FSM::PixmapItemState,actionButtonPixmapItem);
    });

    QAction *actionButtonTextItem = new QAction(QIcon(""),"文本",this);
    actionButtonTextItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonTextItem);
    connect(actionButtonTextItem,&QAction::triggered,this, [this,actionButtonTextItem] () {
        setSceneState(FSM::TextItemState,actionButtonTextItem);
    });
}

void SchematicEditor::createToolButtonWiring()
{
    actionButtonSelect = new QAction(QIcon(""),"选择",this);
    actionButtonSelect->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonSelect);
    connect(actionButtonSelect,&QAction::triggered,this, [this] () {
        setSceneState(FSM::SelectState,actionButtonSelect);
    });

    // 创建布线工具栏
    actionButtonPartItem = new QAction(QIcon(""),"元件",this);
//    actionButtonPartItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonPartItem);
    connect(actionButtonPartItem,&QAction::triggered,this, [this] () {
        if(partSelector->isVisible()){
            partSelector->setVisible(false);
//            if(actionButtonPartItem->isChecked()){
                setSceneState(FSM::SelectState);
//            }
        }else{
            partSelector->setVisible(true);
//            setSceneState(FSM::NoneState,actionButtonPartItem);
        }
    });
    //TODO
//    connect(ui->toolButtonAddPart,&QToolButton::clicked,this,&SchematicEditor::onPartSelectChanged);


    QAction *actionButtonWireSegmentItem = new QAction(QIcon(""),"导线",this);
    actionButtonWireSegmentItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonWireSegmentItem);
    connect(actionButtonWireSegmentItem,&QAction::triggered,this, [this,actionButtonWireSegmentItem] () {
        setSceneState(FSM::WireSegmentItemState,actionButtonWireSegmentItem);
    });


//    QAction *actionPinItem = new QAction(QIcon(""),"管脚"),this);
//    actionPinItem->setCheckable(true);
//    ui->toolBarDrawing->addAction(actionPinItem);
//    connect(actionPinItem,&QAction::triggered,this, [this] () {
//        setSceneState(FSM::PinItemState,actionPinItem);
//    });

    QAction *actionButtonPowerItem = new QAction(QIcon(""),"电源",this);
    actionButtonPowerItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonPowerItem);

    QAction *actionButtonGndItem = new QAction(QIcon(""),"地",this);
    actionButtonGndItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonGndItem);

    QAction *actionButtonBusItem = new QAction(QIcon(""),"总线",this);
    actionButtonBusItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonBusItem);

    QAction *actionButtonBusEntryItem = new QAction(QIcon(""),"入口",this);
    actionButtonBusEntryItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonBusEntryItem);

    QAction *actionButtonOffpageItem = new QAction(QIcon(""),"分页",this);
    actionButtonOffpageItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonOffpageItem);

    QAction *actionButtonJunctionItem = new QAction(QIcon(""),"结点",this);
    actionButtonJunctionItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonJunctionItem);

    QAction *actionButtonNoConnectItem = new QAction(QIcon(""),"空置",this);
    actionButtonNoConnectItem->setCheckable(true);
    ui->toolBarDrawing->addAction(actionButtonNoConnectItem);

    ui->toolBarDrawing->addSeparator();
}

void SchematicEditor::createStatusLabel()
{

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing(2);

    labelSelect = new QLabel("0 item selected");

    QFrame* vLine1 = new QFrame;
    vLine1->setFrameShape(QFrame::VLine);
    vLine1->setFrameShadow(QFrame::Sunken);
    QFrame* vLine2 = new QFrame;
    vLine2->setFrameShape(QFrame::VLine);
    vLine2->setFrameShadow(QFrame::Sunken);
    QFrame* vLine3 = new QFrame;
    vLine3->setFrameShape(QFrame::VLine);
    vLine3->setFrameShadow(QFrame::Sunken);
    QFrame* vLine4 = new QFrame;
    vLine4->setFrameShape(QFrame::VLine);
    vLine4->setFrameShadow(QFrame::Sunken);


    labelScale = new QLabel("100%");
    labelScale->setFixedWidth(50);

    labelPosX = new QLabel("0");
    labelPosX->setFixedWidth(45);

    labelPosY = new QLabel("0");
    labelPosY->setFixedWidth(45);

    labelUnit = new QLabel("密尔");

    layout->addWidget(vLine1);
    layout->addWidget(labelSelect);
    layout->addStretch(400);

    layout->addWidget(vLine2);
    layout->addWidget(labelScale);

    layout->addWidget(vLine3);
    layout->addWidget(labelPosX);
    layout->addWidget(labelPosY);

    layout->addWidget(vLine4);
    layout->addWidget(labelUnit);

//    layout->addSpacing(10);

    static_cast<QHBoxLayout *>(ui->statusBar->layout())->insertLayout(1,layout);
}

void SchematicEditor::createNewSchPage(bool manual)
{
    QString newPageName = "untitled";
    int index = navigator->getMaxSchPageIndex() + 1;
    bool create = true;
    if(manual){
        create = askSchPageName(newPageName,index);
    }
    if(create){
        currentSchView = new SchematicView;
        tabContainer->addTab(currentSchView,newPageName);
        tabContainer->setCurrentWidget(currentSchView);

        SchematicScene *page = currentSchView->schScene;
        page->pageProperty["pageName"] = newPageName;
        page->pageProperty["pageSize"] = defaultPageSize;
        page->pageProperty["index"] = index;

        navigator->addSchPage(page);

        // 页面管理
        schPages.insert(newPageName,page);

        emit pageAdded(page);
    }
}

void SchematicEditor::changeSchPageName(const QString &name)
{

}

bool SchematicEditor::askSchPageName(QString &newPageName,int &index)
{
    NewPageDialog newPageDialog;
    newPageDialog.setIndex(index);
    newPageDialog.exec();

    // 重名问题在newPageDialog内解决
    if(newPageDialog.result()){
        newPageName = newPageDialog.getPageName();
        index = newPageDialog.getIndex();

        return true;
    }

    return false;
}

void SchematicEditor::resetStatusBar()
{
    labelSelect->setText("0 item selected");
    labelPosX->setText("X=0");
    labelPosY->setText("Y=0");
}

void SchematicEditor::initSchematic(const QString &filename)
{
    if(filename.isEmpty()){
        schProperty = json::parse(defaultSchProperty);
        schProperty["schematicName"] = "新建原理图";
        schProperty["createdTime"] = QDateTime::currentSecsSinceEpoch();

        schPinLib = json::parse(defaultPin);
    }else{
        //载入并解析原理图
        schIO->loadSchematic(filename,schematic);
        schProperty["schematicName"] = "www";
        qDebug() << schematic ;

    }
}
