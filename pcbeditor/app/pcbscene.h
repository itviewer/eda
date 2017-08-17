#ifndef PCBSCENE_H
#define PCBSCENE_H

#include <QGraphicsScene>
#include "global.h"

class QUndoStack;
class PCBView;

class PCBScene : public QGraphicsScene
{
    Q_OBJECT

public:
    PCBScene(PCBView *pcbView,QObject *parent = nullptr);

    PCBView *pcbView;
    QUndoStack* undoStack;
    FSM sceneState;

public slots:
    void onSceneStateChanged(const FSM &state);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void keyPressEvent(QKeyEvent* keyEvent);
//    void keyReleaseEvent(QKeyEvent *keyEvent);

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *mouseEvent);

};

#endif // PCBSCENE_H
