#ifndef STATEPOLYGONITEM_H
#define STATEPOLYGONITEM_H

#include "state.h"

class PolygonItem;

class StatePolygonItem : public State
{
public:
    StatePolygonItem(QObject* parent = nullptr);

    bool mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

    bool keyPressEvent(QKeyEvent *keyEvent);

    void cancelDrawing();
private:
    PolygonItem* polygonItem;
    bool isOrthogonalMode;

    bool isHorizontalMode;
    QPointF orthogonalPoint;

    QPolygonF metaPolygon;
};

#endif // STATEPOLYGONITEM_H
