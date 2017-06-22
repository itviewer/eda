#include "poweritem.h"
#include "textitem.h"

PowerItem::PowerItem(SchematicScene *scene, const json &j, QGraphicsItem *parent)
    :AbstractPackageItem(scene,parent)
{

}

void PowerItem::selected()
{

}

void PowerItem::unselected()
{

}

int PowerItem::type() const
{
    return Type;
}

QRectF PowerItem::boundingRect() const
{
    return childrenBoundingRect().adjusted(-5,-5,5,5);
}

QPainterPath PowerItem::shape() const
{
    QPainterPath p;
    return p;
}

void PowerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void PowerItem::setRotation(int angle)
{

}

void PowerItem::keyPressEvent(QKeyEvent *event)
{

}
