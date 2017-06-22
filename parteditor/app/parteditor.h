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

class PartEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit PartEditor(QWidget *parent = 0);
    ~PartEditor();

    QUndoStack *undoStack;
    // TODO 直接将场景设为全局
    PartScene *currentScene() const;

    void setSceneState(const FSM &state,QAction *action = nullptr);

signals:
    void launched();
    void sceneStateChanged(const FSM &state);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void postInit();

    void onActionNewTriggered();

    void onActionZoomInTriggered();
    void onActionZoomOutTriggered();
    void onActionZoomOneTriggered();
private:
    Ui::PartEditor *ui;
    PartView *partView;

    PartLibManager *partLibManager;

    SettingGrid *settingGrid;
    SettingColor *settingColor;
    SettingFont *settingFont;

    QAction *actionButtonUndo;
    QAction *actionButtonRedo;

    QAction *actionButtonSelect;
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

    inline void createStatusLabel();

    void createNewPart();
};

#endif // PARTEDITOR_H
