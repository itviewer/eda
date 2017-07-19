#include "pinitem.h"

#include "lineitem.h"
#include "textitem.h"



PinItem::PinItem(PartScene *scene, const json &j, QGraphicsItem *parent)
    :AbstractPackageItem(scene,parent)
{
//    setZValue(ZValue::PinItemZValue);

    QLineF line;
    line.setP1(j["pinLine"]["geometry"][0]);
    line.setP2(j["pinLine"]["geometry"][1]);
    lineItem = new LineItem(scene,this);
    lineItem->setLine(line);
//    for (auto& shape: j["pinShape"]) {
//        switch (int(shape["type"])) {
//        case Item::LineItemType:
//        {

//        }
//            break;
//        default:
//            break;
//        }
//    }

    pinNameItem= new TextItem(scene,j["pinName"]["text"],this);
    pinNameItem->setPos(j["pinName"]["pos"]);

    shapeRect = lineItem->boundingRect().adjusted(0,-4,0,4);

    setFlags(ItemIsSelectable | ItemIsMovable);
}

void PinItem::selected()
{

}

void PinItem::unselected()
{

}

int PinItem::type() const
{
    return Type;
}

QRectF PinItem::boundingRect() const
{
    return shapeRect;
}

QPainterPath PinItem::shape() const
{
    QPainterPath p;
    p.addRect(shapeRect);
    return p;
}

void PinItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (option->state & QStyle::State_Selected){
        qt_graphicsItem_highlightSelected(this,painter,option);
    }
}

void PinItem::setRotation(int angle)
{
    // 确保角度的绝对值在[0,360]
    angle = qAbs(angle) > 360 ? angle % 360 : angle;
    QGraphicsItemPackage::setRotation(angle);
    // 翻转字体
    if(angle){
        for(QGraphicsItem *item:childItems()){
            if(item->type() == Item::TextItemType){
                static_cast<TextItem *>(item)->followRotation();
            }
        }
    }
}

void PinItem::setPos(const QPointF &pos)
{
    if(snapToGrid){
        AbstractPackageItem::setPos(gridPoint(pos,designGridSize));
    }else{
        AbstractPackageItem::setPos(pos);
    }
}

QVariant PinItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
        case ItemSelectedHasChanged:
            value.toBool() ? selected() : unselected() ;
            break;
        default:
            break;
    }
    return QGraphicsItem::itemChange(change, value);
}
