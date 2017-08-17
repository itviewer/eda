#ifndef PCBEDITOR_H
#define PCBEDITOR_H

#include <QtWidgets>
#include "global.h"

namespace Ui {
    class PCBEditor;
}

class PCBView;
class PCBScene;
class GlobalSetting;

class DockWidget;
class DockWidgetToolBar;
class Navigator;

class PCBEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit PCBEditor(QWidget *parent = nullptr);
    ~PCBEditor();

    PCBScene *pcbScene() const;

    void addDockWidgetToolBar(Qt::DockWidgetArea area, DockWidgetToolBar *toolbar);
    DockWidgetToolBar *getDockWidgetToolBar(Qt::DockWidgetArea area);


    void setSelectStatus(const QString &text);
    void setScaleStatus(const QString &text);
    void setPosStatus(const QPointF &pos);
    void setSceneState(const FSM &state,QAction *action = nullptr);

signals:
    void launch();
    void sceneStateChanged(const FSM &state);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void postInit();
    void onMetadataSaved();
    void onDockAutoHideButtonClicked(bool autoHide);

    void onActionFootprintEditorTriggered();

private:
    Ui::PCBEditor *ui;

    Navigator *navigator;

    DockWidget* navigatorDock;
    PCBView *pcbView;
    GlobalSetting *globalSetting;

    QUndoGroup *undoGroup;

    QHash<Qt::DockWidgetArea,DockWidgetToolBar *> dockToolBars = {
        {Qt::LeftDockWidgetArea,nullptr},
        {Qt::RightDockWidgetArea,nullptr},
        {Qt::BottomDockWidgetArea,nullptr},
        {Qt::TopDockWidgetArea,nullptr}
    };

    QAction *actionUndo;
    QAction *actionRedo;

    QAction *actionSelect;

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


    void createStatusLabel();
};

#endif // PCBEDITOR_H
