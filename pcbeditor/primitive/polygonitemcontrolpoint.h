#ifndef PolygonItemControlPoint_H
#define PolygonItemControlPoint_H

#include "abstractcontrolpoint.h"

class PolygonItem;

class PolygonItemControlPoint : public AbstractControlPoint
{
public:
    PolygonItemControlPoint(PolygonItem *parent = nullptr);
    ~PolygonItemControlPoint();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    PolygonItem *boundingItem;
    QPolygonF metaPolygon;
};

#endif // PolygonItemControlPoint_H
