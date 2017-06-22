#include "portitem.h"
#include "wiresegmentitem.h"
#include "schematicscene.h"

PortItem::PortItem(SchematicScene *scene, const json &j, QGraphicsItem *parent)
    : NodeItem(scene, parent)
{
    setZValue(ZValue::PortItemZValue);
    portState = j["state"];
    switch (portState)
    {
        case PortState::FloatingPort:
        {
            setPen(QPen(QColor("#808080"), 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
            setBrush(Qt::white);
            shapePath.addRect(-3, -3, 6, 6);
            setFlags(ItemSendsScenePositionChanges);
        }
        break;
        default:
            break;
    }
    setPath(shapePath);
    setPos(j["pos"]);
}

int PortItem::type() const
{
    return Type;
}

void PortItem::addNextWireSegmentItem(WireSegmentItem *wireSegmentItem)
{
    wireSegmentItem->attachedStartPort = this;
    attachedNextWireSegmentItems.append(wireSegmentItem);
    portState = PortState::ConnectedPort;
    if(isVisible()){
        hide();
    }
}

void PortItem::addPreWireSegmentItem(WireSegmentItem *wireSegmentItem)
{
    wireSegmentItem->attachedEndPort = this;
    attachedPreWireSegmentItems.append(wireSegmentItem);
    if(isVisible()){
        hide();
    }
}

void PortItem::removeNextWireSegmentItem(WireSegmentItem *wireSegmentItem)
{
    wireSegmentItem->attachedStartPort = nullptr;
    attachedNextWireSegmentItems.removeOne(wireSegmentItem);
    if(attachedNextWireSegmentItems.isEmpty() && attachedPreWireSegmentItems.isEmpty()){
        show();
    }
}

void PortItem::removePreWireSegmentItem(WireSegmentItem *wireSegmentItem)
{
    wireSegmentItem->attachedEndPort = nullptr;
    attachedPreWireSegmentItems.removeOne(wireSegmentItem);
    if(attachedNextWireSegmentItems.isEmpty() && attachedPreWireSegmentItems.isEmpty()){
        show();
    }
}

QVariant PortItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
        case ItemScenePositionHasChanged:
            positionChangedHandler(value.toPointF());
            break;
        default:
            break;
    }
    return QGraphicsItem::itemChange(change, value);
}
