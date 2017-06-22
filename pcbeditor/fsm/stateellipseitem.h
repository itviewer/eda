#ifndef STATEELLIPSEITEM_H
#define STATEELLIPSEITEM_H

#include "state.h"

class EllipseItem;

class StateEllipseItem : public State
{
public:
    StateEllipseItem(QObject* parent = nullptr);

    bool mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

    bool keyPressEvent(QKeyEvent *keyEvent);

    void cancelDrawing();
private:
    EllipseItem* ellipseItem;
    QRectF metaRect;
};

#endif // STATEELLIPSEITEM_H
