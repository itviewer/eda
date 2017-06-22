#ifndef STATETEXTITEM_H
#define STATETEXTITEM_H

#include "state.h"

class TextItem;

class StateTextItem : public State
{
public:
    StateTextItem(QObject* parent = nullptr);

    bool mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

    bool contextMenuEvent(QGraphicsSceneContextMenuEvent *menuEvent);
    bool keyPressEvent(QKeyEvent *keyEvent);

    void cancelDrawing();
private:
    TextItem* textItem;
};

#endif // STATETEXTITEM_H
