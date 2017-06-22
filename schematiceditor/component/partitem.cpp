#include "partitem.h"
#include "rectitem.h"
#include "textitem.h"
#include "pinitem.h"
#include "global.h"
#include <QKeyEvent>

#include "partitemaddcommand.h"
#include "partitemremovecommand.h"
#include "partitemmovecommand.h"

PartItem::PartItem(SchematicScene *scene,int partIndex,QGraphicsItem *parent)
    :AbstractPackageItem(scene,parent),
      partIndexN(partIndex)
{
    metadata["partMd5"] = currentPartMD5;

    partMd5 = currentPartMD5;
    const json &j = currentPart["symbol"][partIndex];

    shapeRect = j["boundingRect"];
    for(auto &shape:j["partShape"]){
        switch (int(shape["type"])) {
        case Item::RectItemType:
        {
            new RectItem(schScene,shape,this);
        }
            break;
        default:
            break;
        }
    }
    for(auto &pin:j["partPin"]){
        json p = schPinLib[int(pin["pinShape"])];
        p["pinName"] = pin["pinName"];
        PinItem *pinItem = new PinItem(schScene,p,this);
        pinItem->setPos(pin["pos"]);
        pinItem->setRotation(pin["rotation"]);

        partPin.append(pinItem);
    }

//    for(auto &property:currentPart["property"]){

//    }
    if(currentPart["property"][0]["show"]){
        TextItem *partName = new TextItem(schScene,currentPart["partName"],this);
        partName->setPos(-20,210);
    }
    if(currentPart["property"][1]["show"]){
        partReferenceItem = new TextItem(schScene,QString::fromStdString(currentPart["partPrefix"]).append('?'),this);
        partReferenceItem->setPos(-10,-20);
    }

    setFlags(ItemIsSelectable | ItemIsFocusable | ItemIsMovable);
    setTransformOriginPoint(shapeRect.center());//???

    setZValue(ZValue::PartItemZValue);
}

PartItem::~PartItem()
{

}

void PartItem::selected()
{
}

void PartItem::unselected()
{
}

int PartItem::type() const
{
    return Type;
}

//json &PartItem::getMetadata()
//{
//    metadata["rotation"] = rotation();
//    metadata["pos"] = pos();
//    return metadata;
//}

QRectF PartItem::boundingRect() const
{
    return childrenBoundingRect().adjusted(-5,-5,5,5);
}

QPainterPath PartItem::shape() const
{
    QPainterPath p;
    p.addRect(shapeRect);
    return p;
}

void PartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (option->state & QStyle::State_Selected){
        qt_graphicsItem_highlightSelected(this,painter,option);
    }
}

void PartItem::setRotation(int angle)
{
    // 确保角度的绝对值在[0,360]
    angle = qAbs(angle) > 360 ? angle % 360 : angle;
    QGraphicsItemPackage::setRotation(angle);
    // 翻转字体
    if(angle){
        for(QGraphicsItem *item:childItems()){
            if(item->type() == Item::PinItemType){
                for(QGraphicsItem *item2:item->childItems()){
                    if(item2->type() == Item::TextItemType){
                        static_cast<TextItem *>(item2)->followRotation();
                    }
                }
            }
        }
    }
}

void PartItem::setReference(bool increaseIndex)
{
    QString partPrefix = currentPart["partPrefix"];
    int partNumbers = currentPart["partNumbers"];

    if(increaseIndex){
        index = partPrefixMaxIndex.value(partPrefix,0) + 1;
        partPrefixMaxIndex.insert(partPrefix,index);//替换当前索引
    }else{
        index = partPrefixMaxIndex.value(partPrefix);
    }
    reference = QString("%1%2").arg(partPrefix).arg(index);
    if(partNumbers > 1){
        if(int(currentPart["partNumbering"])){
            partReference = reference.append(QString("-%1").arg(partIndexN + 1));
        }else{
            partReference = reference.append(QString("-%1").arg(alphabet.at(partIndexN)));
        }
    }else{
        partReference = reference;
    }

    partReferenceItem->setText(partReference);
    metadata["partReference"] = partReference;

    if(!partPrefixIndex.contains(partPrefix,index)){
        partPrefixIndex.insert(partPrefix,index);
    }
}

void PartItem::createCommandAdd()
{
    schScene->pushCommand(new PartItemAddCommand(this),true);
}

void PartItem::createCommandRemove()
{

}

void PartItem::createCommandMove()
{
    schScene->pushCommand(new PartItemMoveCommand(this));
}

void PartItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    // 必须先于父类函数执行 父类函数会重置移动状态
    if(isMoved()){
        createCommandMove();
    }
    AbstractPackageItem::mouseReleaseEvent(mouseEvent);
}

void PartItem::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){
        setRotation(rotation() - 90);
        event->accept();
    }
}
