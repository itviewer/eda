#ifndef ROUNDEDRECTITEMCONTROLPOINT_H
#define ROUNDEDRECTITEMCONTROLPOINT_H

#include "abstractcontrolpoint.h"

class RoundedRectItem;

class RoundedRectItemControlPoint : public AbstractControlPoint
{
public:
    RoundedRectItemControlPoint(RoundedRectItem *parent = nullptr);
    ~RoundedRectItemControlPoint();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
private:
    RoundedRectItem *boundingItem;
    QRectF metaRect;
};

#endif // ROUNDEDRECTITEMCONTROLPOINT_H
