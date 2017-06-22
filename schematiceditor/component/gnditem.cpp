#include "gnditem.h"

GndItem::GndItem(SchematicScene *scene, const json &j, QGraphicsItem *parent)
    :AbstractPackageItem(scene,parent)
{

}

void GndItem::selected()
{

}

void GndItem::unselected()
{

}

int GndItem::type() const
{
    return Type;
}

QRectF GndItem::boundingRect() const
{
    return childrenBoundingRect().adjusted(-5,-5,5,5);
}

QPainterPath GndItem::shape() const
{
    QPainterPath p;
    return p;
}

void GndItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void GndItem::setRotation(int angle)
{

}

void GndItem::keyPressEvent(QKeyEvent *event)
{

}
