#include "junctionitem.h"
#include "schematicscene.h"
#include "wiresegmentitem.h"
#include "wire.h"

JunctionItem::JunctionItem(SchematicScene *scene, const QPointF &center, QGraphicsItem *parent)
    :NodeItem(scene,parent)
{
    setZValue(ZValue::JunctionItemZValue);

    setPen(Qt::NoPen);
    setBrush(QColor(schColor.selection));
    shapePath.addEllipse(-4,-4,8,8);
    setFlags(ItemIsSelectable | ItemIsMovable | ItemSendsScenePositionChanges);

    setPath(shapePath);
    setPos(center);

    setReference();
    schScene->addJunction(this);
}

void JunctionItem::selected()
{
    // 以该结点为终点的线段
    for(WireSegmentItem *item:attachedPreWireSegmentItems) {
        if(!item->isSelected()) {
            item->setSelected(true);
        }
    }
    // 以该结点为始点的线段
    for(WireSegmentItem *item:attachedNextWireSegmentItems) {
        if(!item->isSelected()) {
            item->setSelected(true);
        }
    }
}

int JunctionItem::type() const
{
    return Type;
}

int JunctionItem::attachedWireCount()
{
    return attachedPreWireSegmentItems.count() + attachedNextWireSegmentItems.count();
}

void JunctionItem::addNextWireSegmentItem(WireSegmentItem *wireSegmentItem)
{
    wireSegmentItem->attachedStartJunction = this;
    attachedNextWireSegmentItems.append(wireSegmentItem);
}

void JunctionItem::addPreWireSegmentItem(WireSegmentItem *wireSegmentItem)
{
    wireSegmentItem->attachedEndJunction = this;
    attachedPreWireSegmentItems.append(wireSegmentItem);
}

void JunctionItem::removeNextWireSegmentItem(WireSegmentItem *wireSegmentItem)
{
    wireSegmentItem->attachedStartJunction = nullptr;
    attachedNextWireSegmentItems.removeOne(wireSegmentItem);
}

void JunctionItem::removePreWireSegmentItem(WireSegmentItem *wireSegmentItem)
{
    wireSegmentItem->attachedEndJunction = nullptr;
    attachedPreWireSegmentItems.removeOne(wireSegmentItem);
}

bool JunctionItem::mergeAttachedWire() const
{
    if(attachedPreWireSegmentItems.count() == 1 && attachedNextWireSegmentItems.count() == 1){
       attachedPreWireSegmentItems.first()->attachedWire->merge(attachedNextWireSegmentItems.first()->attachedWire);
       return true;
    }
    return false;
}

void JunctionItem::setAttachedNet(const QString &net)
{
    netName = net;
}

const QString JunctionItem::attachedNet()
{
    return netName;
}

void JunctionItem::setReference()
{
    junctionMaxIndex += 1;
    reference = QString("@J%1").arg(junctionMaxIndex);
}

QVariant JunctionItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch(change) {
        case ItemSelectedHasChanged:
            if(value.toBool()){
                selected();
            }
            break;
        case ItemScenePositionHasChanged:
            // 只要被选中 则所有相连的导线段都被选中
            if(!isSelected()){
                positionChangedHandler(value.toPointF());
            }
            break;
        default:
            break;
    }
    return QGraphicsItem::itemChange(change, value);
}
