#ifndef STATEPINITEM_H
#define STATEPINITEM_H

#include "state.h"

class PinItem;

class StatePinItem : public State
{
public:
    StatePinItem(QObject* parent = nullptr);

    bool mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
private:
    PinItem* pinItem;
};

#endif // STATEPINITEM_H
