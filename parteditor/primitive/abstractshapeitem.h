#ifndef ABSTRACTSHAPEITEM_H
#define ABSTRACTSHAPEITEM_H

#include "global.h"
#include <QPen>
#include <QKeyEvent>

class QGraphicsItem;

class AbstractShapeItem
{
public:
    AbstractShapeItem(PartScene *scene,QGraphicsItem *child);

    PartScene *partScene;

    QPen drawingPen;
    QPen selectedPen;
    QPen normalPen;

private:
    QGraphicsItem *childItem;
};

#endif // ABSTRACTSHAPEITEM_H
