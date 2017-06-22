#ifndef STATEPOLYLINEITEM_H
#define STATEPOLYLINEITEM_H

#include "state.h"

class PolylineItem;

class StatePolylineItem : public State
{
public:
    StatePolylineItem(QObject* parent = nullptr);

    bool mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

    bool keyPressEvent(QKeyEvent *keyEvent);

    void cancelDrawing();
private:
    PolylineItem* polylineItem;
    Angle angleMode;

    bool isHorizontalMode;
    QPointF orthogonalPoint;

    QPolygonF metaPolyline;
};

#endif // STATEPOLYLINEITEM_H
