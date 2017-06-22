#ifndef ABSTRACTSHAPEITEM_H
#define ABSTRACTSHAPEITEM_H

#include "global.h"
#include <QPen>
#include <QKeyEvent>

class QGraphicsItem;
class PCBScene;

class AbstractShapeItem
{
public:
    AbstractShapeItem(PCBScene *scene,QGraphicsItem *child);

    PCBScene *pcbScene;

    QPen drawingPen;
    QPen selectedPen;
    QPen normalPen;

private:
    QGraphicsItem *childItem;
};

#endif // ABSTRACTSHAPEITEM_H
