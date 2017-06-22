#ifndef ABSTRACTCONTROLPOINT_H
#define ABSTRACTCONTROLPOINT_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
class SchematicScene;

class AbstractControlPoint : public QGraphicsRectItem
{
public:
    AbstractControlPoint(QGraphicsItem *parent = nullptr);
    ~AbstractControlPoint();

    SchematicScene *schScene;
    int flag;

};

#endif // ABSTRACTCONTROLPOINT_H
