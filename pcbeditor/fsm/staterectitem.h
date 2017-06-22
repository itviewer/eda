#ifndef STATERECTITEM_H
#define STATERECTITEM_H

#include "state.h"

class RectItem;

class StateRectItem : public State
{
public:
    StateRectItem(QObject* parent = nullptr);

    bool mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

    bool keyPressEvent(QKeyEvent *keyEvent);

    void cancelDrawing();
private:
    RectItem* rectItem;
    QRectF metaRect;
};

#endif // STATERECTITEM_H
