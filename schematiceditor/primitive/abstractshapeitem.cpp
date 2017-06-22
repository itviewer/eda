#include "abstractshapeitem.h"
#include <QGraphicsItem>

AbstractShapeItem::AbstractShapeItem(SchematicScene *scene, QGraphicsItem *child)
    :schScene(scene),
      childItem(child)
{
    //    qDebug() << child ;
}
