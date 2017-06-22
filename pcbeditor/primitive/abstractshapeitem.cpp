#include "abstractshapeitem.h"
#include <QGraphicsItem>

AbstractShapeItem::AbstractShapeItem(PCBScene *scene, QGraphicsItem *child)
    :pcbScene(scene),
      childItem(child)
{
    //    qDebug() << child ;
}
