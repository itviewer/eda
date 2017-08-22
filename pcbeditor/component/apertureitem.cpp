#include "apertureitem.h"

ApertureItem::ApertureItem(PCBScene *scene, const json &j, QGraphicsItem *parent)
    :AbstractPackageItem(scene,parent)
{
    shapeItem = new QGraphicsPathItem(this);

    if(j["geometry"]["hole"] > 0){
        holeItem = new QGraphicsPathItem(this);
    }
    setGeometry(j["geometry"]);
//    setOpacity(0);
}

void ApertureItem::selected()
{

}

void ApertureItem::unselected()
{

}

int ApertureItem::type() const
{
    return Type;
}

QRectF ApertureItem::boundingRect() const
{
    return shapeItem->boundingRect();
}

QPainterPath ApertureItem::shape() const
{
    return shapeItem->shape();
}

void ApertureItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void ApertureItem::setGeometry(const json &geometry)
{
    shapeItem->setPen(Qt::NoPen);
    shapeItem->setBrush(Qt::blue);
    qreal rx = geometry["size"][0];
    QPainterPath p;
    p.addEllipse(QPointF(0,0),rx,rx);

    shapeItem->setPath(p);

    if(holeItem){
        qreal hole = geometry["hole"];

        holeItem->setPen(Qt::NoPen);
        holeItem->setBrush(Qt::darkBlue);

        QPainterPath pp;
        pp.addEllipse(QPointF(0,0),hole,hole);

        holeItem->setPath(pp);
    }
}
