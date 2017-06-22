#ifndef PolylineItemControlPoint_H
#define PolylineItemControlPoint_H

#include "abstractcontrolpoint.h"

class PolylineItem;

class PolylineItemControlPoint : public AbstractControlPoint
{
public:
    PolylineItemControlPoint(PolylineItem *parent = nullptr);
    ~PolylineItemControlPoint();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    PolylineItem *boundingItem;
    QPolygonF metaPolyline;
};

#endif // PolylineItemControlPoint_H
