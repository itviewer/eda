#ifndef EllipseItemControlPoint_H
#define EllipseItemControlPoint_H

#include "abstractcontrolpoint.h"

class EllipseItem;

class EllipseItemControlPoint : public AbstractControlPoint
{
public:
    EllipseItemControlPoint(EllipseItem *parent = nullptr);
    ~EllipseItemControlPoint();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
private:
    EllipseItem *boundingItem;
    QRectF metaRect;
};

#endif // EllipseItemControlPoint_H
