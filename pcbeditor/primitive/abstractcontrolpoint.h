#ifndef ABSTRACTCONTROLPOINT_H
#define ABSTRACTCONTROLPOINT_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
class PCBScene;

class AbstractControlPoint : public QGraphicsRectItem
{
public:
    AbstractControlPoint(QGraphicsItem *parent = nullptr);
    ~AbstractControlPoint();

    PCBScene *pcbScene;
    int flag;

};

#endif // ABSTRACTCONTROLPOINT_H
