#ifndef NODEITEM_H
#define NODEITEM_H

#include <QGraphicsPathItem>
#include "global.h"

class WireSegmentItem;

class NodeItem : public QGraphicsPathItem
{
public:

    NodeItem(SchematicScene *scene,QGraphicsItem *parent = nullptr);

    enum {
        Type = Item::NodeItemType
    };

    SchematicScene *schScene;
    QPainterPath shapePath;

    QVector<WireSegmentItem *> attachedPreWireSegmentItems;
    QVector<WireSegmentItem *> attachedNextWireSegmentItems;

    virtual int type() const;
    QPainterPath shape() const;

    void wireSegmentItemChangedHandler(WireSegmentItem *wireSegmentItem,bool startNode);
    void positionChangedHandler(const QPointF &pos);
};

#endif // NODEITEM_H
