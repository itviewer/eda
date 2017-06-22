#ifndef ABSTRACTCONTROLPOINT_H
#define ABSTRACTCONTROLPOINT_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
class PartScene;

class AbstractControlPoint : public QGraphicsRectItem
{
public:
    AbstractControlPoint(QGraphicsItem *parent = nullptr);
    ~AbstractControlPoint();

    PartScene *partScene;
    int flag;

};

#endif // ABSTRACTCONTROLPOINT_H
