#include "abstractshapeitem.h"
#include <QGraphicsItem>

AbstractShapeItem::AbstractShapeItem(PartScene *scene, QGraphicsItem *child)
    :partScene(scene),
      childItem(child)
{
    //    qDebug() << child ;
}
