#ifndef AIDERECTITEMCONTROLPOINT_H
#define AIDERECTITEMCONTROLPOINT_H

#include "abstractcontrolpoint.h"

class AideRectItem;

class AideRectItemControlPoint : public AbstractControlPoint
{
public:
    AideRectItemControlPoint(AideRectItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
private:
    AideRectItem *boundingItem;
    QRectF metaRect;
};


#endif // AIDERECTITEMCONTROLPOINT_H
