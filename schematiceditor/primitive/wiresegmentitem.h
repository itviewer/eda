#ifndef WIRESEGMENTITEM_H
#define WIRESEGMENTITEM_H

#include <QGraphicsLineItem>

#include "abstractshapeitem.h"

class Wire;
class JunctionItem;
class PortItem;
class QUndoCommand;

class WireSegmentItem : public QGraphicsLineItem,public AbstractShapeItem
{
public:
    WireSegmentItem(SchematicScene *scene,QGraphicsItem *parent = nullptr);
    ~WireSegmentItem();

    enum {
        Type = Item::WireSegmentItemType
    };

    Wire *attachedWire;
    // 性能优先 不使用set/get方式
    JunctionItem *attachedStartJunction;
    JunctionItem *attachedEndJunction;
    PortItem *attachedStartPort;
    PortItem *attachedEndPort;

    // previous/next item
    WireSegmentItem *preItem;
    WireSegmentItem *nextItem;

    bool isHorizontalMode;

    void selected();
    void unselected();
    int type() const;
    qreal length() const;
    json &getMetadata() Q_DECL_OVERRIDE;

    void itemChangedHandler();

    void preItemChangedHandler();
    void nextItemChangedHandler();

    void preNodeChangedHandler(const QPointF &pos);
    void nextNodeChangedHandler(const QPointF &pos);

    const QPointF startPoint();
    const QPointF endPoint();
    const QString attachedNet();

    WireSegmentItem *junctionSplit(const QPointF &pos);

    void createCommandRemove();
    void createCommandMove();
    void createCommandChangeGeometry();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
//    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    void keyPressEvent(QKeyEvent* keyEvent);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
private:
    bool isMoving;
    void drawControlPoints();

    void removedHandler();

    void removeItem();
};

#endif // WIRESEGMENTITEM_H
