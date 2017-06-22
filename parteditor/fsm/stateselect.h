#ifndef STATESELECT_H
#define STATESELECT_H

#include "state.h"

class StateSelect : public State
{
public:
    StateSelect(QObject* parent = nullptr);

    bool mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

    bool contextMenuEvent(QGraphicsSceneContextMenuEvent *menuEvent);
    bool keyPressEvent(QKeyEvent *keyEvent);

private:
    QMenu *shapeContextMenu;
    void createShapeContextMenu();

};

#endif // STATESELECT_H
