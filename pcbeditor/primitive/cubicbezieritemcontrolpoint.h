#ifndef CUBICBEZIERITEMCONTROLPOINT_H
#define CUBICBEZIERITEMCONTROLPOINT_H

#include "abstractcontrolpoint.h"

class CubicBezierItem;

class CubicBezierItemControlPoint : public AbstractControlPoint
{
public:
    CubicBezierItemControlPoint(CubicBezierItem *parent = nullptr);
    ~CubicBezierItemControlPoint();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
private:
    CubicBezierItem *boundingItem;
    QPolygonF metaPolygon;
};

#endif // CUBICBEZIERITEMCONTROLPOINT_H
