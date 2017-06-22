#include "offpageitem.h"

OffpageItem::OffpageItem(SchematicScene *scene, const json &j, QGraphicsItem *parent)
    :AbstractPackageItem(scene,parent)
{

}

void OffpageItem::selected()
{

}

void OffpageItem::unselected()
{

}

int OffpageItem::type() const
{
    return Type;
}

QRectF OffpageItem::boundingRect() const
{
    return childrenBoundingRect().adjusted(-5,-5,5,5);
}

QPainterPath OffpageItem::shape() const
{
    QPainterPath p;
    return p;
}

void OffpageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void OffpageItem::setRotation(int angle)
{

}

void OffpageItem::keyPressEvent(QKeyEvent *event)
{

}
