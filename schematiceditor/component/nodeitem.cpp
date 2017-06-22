#include "nodeitem.h"
#include "wiresegmentitem.h"
#include <QPainterPathStroker>

#include "schematicscene.h"

NodeItem::NodeItem(SchematicScene *scene, QGraphicsItem *parent)
    :QGraphicsPathItem(parent),
     schScene(scene)
{
}

int NodeItem::type() const
{
    return Type;
}

QPainterPath NodeItem::shape() const
{
    QPainterPath path;
    path.addRect(shapePath.boundingRect());
    return path;
}

// 被动改变
void NodeItem::wireSegmentItemChangedHandler(WireSegmentItem *wireSegmentItem, bool startNode)
{
    const QPointF newPos = startNode ? wireSegmentItem->startPoint() : wireSegmentItem->endPoint();

    // 一定没有处于选中状态
    setPos(newPos);
}

// 主动改变
void NodeItem::positionChangedHandler(const QPointF &pos)
{
    // 以该结点为终点的线段
    for(WireSegmentItem *item:attachedPreWireSegmentItems) {
        if(!item->isSelected()) {
            item->nextNodeChangedHandler(pos);
        }
    }
    // 以该结点为始点的线段
    for(WireSegmentItem *item:attachedNextWireSegmentItems) {
        if(!item->isSelected()) {
            item->preNodeChangedHandler(pos);
        }
    }
}
