#ifndef SCHEMATICEDITOR_H
#define SCHEMATICEDITOR_H

#include <QtWidgets>
#include "global.h"

namespace Ui {
class SchematicEditor;
}

class GlobalSetting;
class SchematicView;
class SchematicScene;
class StateMachine;
class SchematicIO;

class DockWidgetToolBar;

class TabContainer;

class DockWidget;
class Navigator;
class PartSelector;
class PartLibManager;

class SchematicEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit SchematicEditor(QWidget *parent = 0);
    ~SchematicEditor();

    // 共外部类使用的共享指针
    SchematicIO *schIO;
    TabContainer *tabContainer;

    QUndoGroup *undoGroup;
    QAction *actionButtonCut;
    QAction *actionButtonCopy;
    QAction *actionButtonSnapToGrid;

    SchematicScene *currentScene() const;

    void addDockWidgetToolBar(Qt::DockWidgetArea area, DockWidgetToolBar *toolbar);
    DockWidgetToolBar *getDockWidgetToolBar(Qt::DockWidgetArea area);


    void setSelectStatus(const QString &text);
    void setScaleStatus(const QString &text);
    void setPosStatus(const QPointF &pos);
    void setSceneState(const FSM &state,QAction *action = nullptr);

    void setFocusOfCurrentView();

signals:
    void launched();
    void sceneStateChanged(const FSM &state);
    void pageAdded(SchematicScene *page);

public slots:
    void onCurrentViewChanged(const int &index);
    void onPartSelectChanged();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void postInit();
    void onMetadataSaved();
    void onDockAutoHideButtonClicked(bool autoHide);

    void onActionNewTriggered();
    void onActionOpenTriggered();
    void onActionSaveTriggered();
    void onActionSaveAllTriggered();
    void onActionSaveAsTriggered();
    void onActionCloseTriggered();

    void onActionZoomInTriggered();
    void onActionZoomOutTriggered();
    void onActionZoomOneTriggered();
    void onActionZoomHomeTriggered();

    void onActionPartEditorTriggered();

private:
    Ui::SchematicEditor *ui;
    Navigator *navigator;
    PartSelector *partSelector;

    SchematicView *currentSchView;
    GlobalSetting *globalSetting;
    PartLibManager *partLibManager;

    DockWidget* navigatorDock;

    QFutureWatcher<void> schSaveWatcher;
    QFuture<void> schSaveFuture;
    QVector<SchematicScene *> needSavedPage;

    QHash<Qt::DockWidgetArea,DockWidgetToolBar *> dockToolBars = {
        {Qt::LeftDockWidgetArea,nullptr},
        {Qt::RightDockWidgetArea,nullptr},
        {Qt::BottomDockWidgetArea,nullptr},
        {Qt::TopDockWidgetArea,nullptr}
    };

    QLabel *labelSelect;
    QLabel *labelScale;
    QLabel *labelPosX;
    QLabel *labelPosY;
    QLabel *labelUnit;

    QAction *actionButtonUndo;
    QAction *actionButtonRedo;

    QAction *actionButtonSelect;
    QAction *actionButtonPartItem;

    QString currentProject;
    QAction *currentStateAction;

    inline void init();

    inline void createMenuFile();
    inline void createMenuEdit();
    inline void createMenuView();
    inline void createMenuTools();
    inline void createMenuSetup();
    inline void createMenuHelp();

    inline void createToolButtonMain();
    inline void createToolButtonDrawing();
    inline void createToolButtonWiring();

    inline void createStatusLabel();

    void createNewSchPage(bool manual = false);
    void changeSchPageName(const QString &name);
    bool askSchPageName(QString &newPageName,int &index);

    void resetStatusBar();

    void initSchematic(const QString &filename = "");
};

#endif // SCHEMATICEDITOR_H
