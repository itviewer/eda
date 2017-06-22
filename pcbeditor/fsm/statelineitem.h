#ifndef STATELINEITEM_H
#define STATELINEITEM_H

#include "state.h"

class LineItem;

class StateLineItem : public State
{
public:
    StateLineItem(QObject* parent = nullptr);

    bool mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

    bool keyPressEvent(QKeyEvent *keyEvent);

    void cancelDrawing();
private:
    LineItem* lineItem;
    QLineF metaLine;
};

#endif // STATELINEITEM_H
