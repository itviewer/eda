#ifndef PARTEDITOR_H
#define PARTEDITOR_H

#include <QtWidgets>
#include "global.h"

namespace Ui {
    class PartEditor;
}

class PartView;
class PartScene;

class SettingGrid;
class SettingColor;
class SettingFont;

class PartLibManager;

class QRemoteObjectHost;
class PartEditorRPC;

class PartEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit PartEditor(QWidget *parent = 0);
    ~PartEditor();

    QUndoStack *undoStack;
    QAction *actionButtonSnapToGrid;

    // TODO 直接将场景设为全局
    PartScene *currentScene() const;

    void setSceneState(const FSM &state,QAction *action = nullptr);

signals:
    void launched();
    void sceneStateChanged(const FSM &state);
    void partNumberChanged();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void postInit();

    void onActionNewTriggered();

    void onActionPrePartTriggered();
    void onActionNextPartTriggered();
    void onActionZoomInTriggered();
    void onActionZoomOutTriggered();
    void onActionZoomOneTriggered();

private:
    Ui::PartEditor *ui;
    PartView *partView;

//    QRemoteObjectHost *rpcNode;
//    PartEditorRPC *partEditorRPC;

    PartLibManager *partLibManager;

    SettingGrid *settingGrid;
    SettingColor *settingColor;
    SettingFont *settingFont;

    QAction *actionButtonUndo;
    QAction *actionButtonRedo;

    QAction *actionButtonSelect;
    QAction *currentStateAction;

    QAction *actionMenuPrePart;
    QAction *actionMenuNextPart;

    inline void init();

    inline void createMenuFile();
    inline void createMenuEdit();
    inline void createMenuView();
    inline void createMenuTools();
    inline void createMenuSetup();
    inline void createMenuHelp();

    inline void createToolButtonMain();
    inline void createToolButtonDrawing();

    inline void createStatusLabel();

    void createNewPart(bool manual = false);
};

#endif // PARTEDITOR_H
