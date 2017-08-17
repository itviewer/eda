#ifndef STATEVIAITEM_H
#define STATEVIAITEM_H

#include "state.h"

class StateViaItem : public State
{
public:
    StateViaItem(QObject* parent = nullptr);

    bool mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

    bool keyPressEvent(QKeyEvent *keyEvent);

    void cancelDrawing();
};

#endif // STATEVIAITEM_H
