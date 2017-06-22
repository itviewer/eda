#include "pinitem.h"
#include "lineitem.h"
#include "textitem.h"

#include "global.h"
#include <QPainterPath>
#include <QKeyEvent>

#include "portitem.h"
//#include "partitem.h"

PinItem::PinItem(PartScene *scene, QGraphicsItem *parent)
    :AbstractPackageItem(scene,parent)
{
    setFiltersChildEvents(true);
//    setHandlesChildEvents(true);

    setZValue(ZValue::PinItemZValue);
}

PinItem::PinItem(PartScene *scene, const json &j, QGraphicsItem *parent)
    :AbstractPackageItem(scene,parent)
{
    setZValue(ZValue::PinItemZValue);

    QLineF line;
    line.setP1(j["pinLine"]["geometry"][0]);
    line.setP2(j["pinLine"]["geometry"][1]);
    lineItem = new LineItem(partScene,this);
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

    pinNameItem= new TextItem(partScene,j["pinName"]["text"],this);
    pinNameItem->setPos(j["pinName"]["pos"]);

    shapeRect = lineItem->boundingRect().adjusted(0,-4,0,4);

    port = new PortItem(partScene,j["pinPort"],this);
}

PinItem::~PinItem()
{

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

void PinItem::setPinName(const json &name)
{
    pinNameItem->setText(name);
}

void PinItem::setPinNubmer(const json &number)
{

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

void PinItem::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){
        setRotation(rotation() - 90);
        event->accept();
    }
}

//bool PinItem::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
//{
////    qDebug() << event;

//    return true;
//}
