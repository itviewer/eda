#ifndef LINEITEMCONTROLPOINT_H
#define LINEITEMCONTROLPOINT_H

#include "abstractcontrolpoint.h"

class LineItem;

class LineItemControlPoint : public AbstractControlPoint
{
public:
    LineItemControlPoint(LineItem *parent = nullptr);
    ~LineItemControlPoint();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    LineItem *boundingItem;
    QLineF metaLine;
};

#endif // LINEITEMCONTROLPOINT_H
