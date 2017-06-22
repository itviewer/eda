#ifndef STATEWIREITEM_H
#define STATEWIREITEM_H

#include "state.h"

class WireSegmentItem;
class NodeItem;
class Wire;

class StateWireSegmentItem : public State
{
public:
    StateWireSegmentItem(QObject* parent = nullptr);

    bool mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

    bool contextMenuEvent(QGraphicsSceneContextMenuEvent *menuEvent);
    bool keyPressEvent(QKeyEvent *keyEvent);

    void cancelDrawing();
private:
    WireSegmentItem* wireSegmentItem;
    WireSegmentItem* nextWireSegmentItem;

    WireSegmentItem* startWireSegmentItem;
    WireSegmentItem* endWireSegmentItem;

    Wire* wire;

    bool isHorizontalMode;
    QPointF orthogonalPoint;

    void endDrawing(NodeItem *endNode = nullptr);

    QMenu *contextMenu;
    void createContextMenu();
};

#endif // STATEWIREITEM_H
