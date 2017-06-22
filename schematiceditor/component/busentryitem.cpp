#include "busentryitem.h"

BusEntryItem::BusEntryItem(SchematicScene *scene, const json &j, QGraphicsItem *parent)
    :AbstractPackageItem(scene,parent)
{

}

void BusEntryItem::selected()
{

}

void BusEntryItem::unselected()
{

}

int BusEntryItem::type() const
{
    return Type;
}

QRectF BusEntryItem::boundingRect() const
{
    return childrenBoundingRect().adjusted(-5,-5,5,5);
}

QPainterPath BusEntryItem::shape() const
{
    QPainterPath p;
    return p;
}

void BusEntryItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void BusEntryItem::setRotation(int angle)
{

}

void BusEntryItem::keyPressEvent(QKeyEvent *event)
{

}
