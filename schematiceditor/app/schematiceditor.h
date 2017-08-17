#ifndef SCHEMATICEDITOR_H
#define SCHEMATICEDITOR_H

#include <QtWidgets>
#include "global.h"

namespace Ui {
class SchematicEditor;
}

class GlobalSetting;
class GlobalSettingColorScheme;
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
    void colorSchemeChanged(const QString &scheme);

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
    GlobalSettingColorScheme *globalSettingColorScheme;
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

    void createMenuFile();
    void createMenuEdit();
    void createMenuView();
    void createMenuTools();
    void createMenuSetup();
    void createMenuHelp();

    void createToolButtonMain();
    void createToolButtonDrawing();
    void createToolButtonWiring();

    void createStatusLabel();

    void createNewSchPage(bool manual = false);
    void changeSchPageName(const QString &name);
    bool askSchPageName(QString &newPageName,int &index);

    void resetStatusBar();

    void initSchematic(const QString &filename = "");
};

#endif // SCHEMATICEDITOR_H
