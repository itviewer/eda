#ifndef WireSegmentItemControlPoint_H
#define WireSegmentItemControlPoint_H

#include "abstractcontrolpoint.h"

class WireSegmentItem;

class WireSegmentItemControlPoint : public AbstractControlPoint
{
public:
    WireSegmentItemControlPoint(WireSegmentItem *parent = nullptr);
    ~WireSegmentItemControlPoint();

    WireSegmentItem *boundingItem;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    QLineF metaLine;
    QLineF tmpLine;
};

#endif // WireSegmentItemControlPoint_H
