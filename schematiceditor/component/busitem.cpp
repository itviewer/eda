#include "busitem.h"

BusItem::BusItem(SchematicScene *scene, const json &j, QGraphicsItem *parent)
    :AbstractPackageItem(scene,parent)
{

}

void BusItem::selected()
{

}

void BusItem::unselected()
{

}

int BusItem::type() const
{
    return Type;
}

QRectF BusItem::boundingRect() const
{
    return childrenBoundingRect().adjusted(-5,-5,5,5);
}

QPainterPath BusItem::shape() const
{
    QPainterPath p;
    return p;
}

void BusItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void BusItem::setRotation(int angle)
{

}

void BusItem::keyPressEvent(QKeyEvent *event)
{

}
