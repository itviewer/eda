#ifndef RECTITEMCONTROLPOINT_H
#define RECTITEMCONTROLPOINT_H

#include "abstractcontrolpoint.h"

class RectItem;

class RectItemControlPoint : public AbstractControlPoint
{
public:
    RectItemControlPoint(RectItem *parent = nullptr);
    ~RectItemControlPoint();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
private:
    RectItem *boundingItem;
    QRectF metaRect;
};

#endif // RECTITEMCONTROLPOINT_H
