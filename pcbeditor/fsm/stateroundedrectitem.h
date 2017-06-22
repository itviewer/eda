#ifndef STATEROUNDEDRECTITEM_H
#define STATEROUNDEDRECTITEM_H

#include "state.h"

class RoundedRectItem;

class StateRoundedRectItem : public State
{
public:
    StateRoundedRectItem(QObject* parent = nullptr);

    bool mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

    bool keyPressEvent(QKeyEvent *keyEvent);

    void cancelDrawing();
private:
    RoundedRectItem* rectItem;
    QRectF metaRect;
    qreal radius;
};

#endif // STATEROUNDEDRECTITEM_H
