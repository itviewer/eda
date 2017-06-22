#ifndef JUNCTIONITEM_H
#define JUNCTIONITEM_H

#include "nodeitem.h"

class JunctionItem : public NodeItem
{
public:
    JunctionItem(SchematicScene *scene,const QPointF &center,QGraphicsItem *parent = nullptr);

    enum {
        Type = Item::JunctionItemType
    };

    QString reference;

    void selected();
    int type() const Q_DECL_OVERRIDE;

    int attachedWireCount();
    void addNextWireSegmentItem(WireSegmentItem *wireSegmentItem);
    void addPreWireSegmentItem(WireSegmentItem *wireSegmentItem);

    void removeNextWireSegmentItem(WireSegmentItem *wireSegmentItem);
    void removePreWireSegmentItem(WireSegmentItem *wireSegmentItem);

    bool mergeAttachedWire() const;
    void setAttachedNet(const QString &net);
    const QString attachedNet();

    void setReference();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
private:
    QString netName;
};

#endif // JUNCTIONITEM_H
