#ifndef PORTITEM_H
#define PORTITEM_H

#include "nodeitem.h"

class PortItem : public NodeItem
{
public:
    PortItem(SchematicScene *scene,const json &j,QGraphicsItem *parent = nullptr);

    enum {
        Type = Item::PortItemType
    };

    int type() const Q_DECL_OVERRIDE;

    void addNextWireSegmentItem(WireSegmentItem *wireSegmentItem);
    void addPreWireSegmentItem(WireSegmentItem *wireSegmentItem);

    void removeNextWireSegmentItem(WireSegmentItem *wireSegmentItem);
    void removePreWireSegmentItem(WireSegmentItem *wireSegmentItem);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    PortState portState;
};

#endif // PORTITEM_H
