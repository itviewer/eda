#include "statewiresegmentitem.h"
#include "wiresegmentitem.h"
#include "wire.h"
#include "junctionitem.h"
#include "portitem.h"
#include "schematicview.h"

#include "wirespiltcommand.h"

StateWireSegmentItem::StateWireSegmentItem(QObject *parent)
    : State(parent),
      wireSegmentItem(nullptr),
      nextWireSegmentItem(nullptr),
      startWireSegmentItem(nullptr),
      endWireSegmentItem(nullptr),
      wire(nullptr),
      isHorizontalMode(true)
{

}

bool StateWireSegmentItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() == Qt::LeftButton) {
        mousePressScenePoint = mouseEvent->scenePos();
        if(!wireSegmentItem) {
            firstMousePressScenePoint = mousePressScenePoint;

            wireSegmentItem =  new WireSegmentItem(schScene);
            wireSegmentItem->setPos(mousePressScenePoint);

            nextWireSegmentItem = new WireSegmentItem(schScene);
            nextWireSegmentItem->preItem = wireSegmentItem;
            wireSegmentItem->nextItem = nextWireSegmentItem;

            schScene->addItem(wireSegmentItem);
            schScene->addItem(nextWireSegmentItem);

            schScene->clearSelection();
            isDrawing = true;

            wire = new Wire(schScene);
        }
    }

    return true;
}

bool StateWireSegmentItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(wireSegmentItem) {
        mouseMoveScenePoint = mouseEvent->scenePos();
        const QPointF ep = wireSegmentItem->mapFromScene(mouseMoveScenePoint);
        if(ep.y() == 0) {
            isHorizontalMode = true;
        } else if(ep.x() == 0) {
            isHorizontalMode = false;
        }
        if(isHorizontalMode) {
            orthogonalPoint.setX(ep.x());
            orthogonalPoint.setY(0);
            QLineF tmpLine;
            tmpLine.setP2(orthogonalPoint);
            wireSegmentItem->setLine(tmpLine);
        } else {
            orthogonalPoint.setX(0);
            orthogonalPoint.setY(ep.y());
            QLineF tmpLine;
            tmpLine.setP2(orthogonalPoint);
            wireSegmentItem->setLine(tmpLine);
        }
        nextWireSegmentItem->setPos(wireSegmentItem->mapToScene(orthogonalPoint));
        QLineF next;
        next.setP2(nextWireSegmentItem->mapFromScene(mouseMoveScenePoint));
        nextWireSegmentItem->setLine(next);
    }


    return true;
}

bool StateWireSegmentItem ::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(wireSegmentItem) {
        mouseReleaseScenePoint = mouseEvent->scenePos();
        if((mouseReleaseScenePoint != firstMousePressScenePoint) && (mouseReleaseScenePoint != lastMouseReleaseScenePoint)) {
            if(wireSegmentItem->length() > 5){
                wireSegmentItem->isHorizontalMode = isHorizontalMode;
                nextWireSegmentItem->isHorizontalMode = !isHorizontalMode;

                if(wire->isEmpty()){
                    QGraphicsItem *item = schScene->itemAt(firstMousePressScenePoint, QTransform());
                    if(item) {
                        switch(item->type()) {
                            case Item::PortItemType: {
                                PortItem *port = qgraphicsitem_cast<PortItem *>(item);
                                port->addNextWireSegmentItem(wireSegmentItem);
                            }
                            break;
                            case Item::WireSegmentItemType: {
                                QList<QGraphicsItem *> items = schScene->items(firstMousePressScenePoint);
                                int i = 0;
                                for (QGraphicsItem *it : items) {
                                    if (it == wireSegmentItem || it->type() != Item::WireSegmentItemType) {
                                        items.removeAt(i);
                                    }
                                    i++;
                                }
                                if (!items.isEmpty()) {
                                    item = items.first();
                                    startWireSegmentItem = qgraphicsitem_cast<WireSegmentItem *>(item);
                                    if(firstMousePressScenePoint == startWireSegmentItem->startPoint()){
                                        if(startWireSegmentItem->preItem){
                                            qDebug() << "111111" ;
                                            JunctionItem *junction = new JunctionItem(schScene, firstMousePressScenePoint);
                                            schScene->addItem(junction);
                                            junction->setAttachedNet(startWireSegmentItem->attachedNet());
                                            junction->addNextWireSegmentItem(wireSegmentItem);
                                            preChildCommands.append(new WireSpiltCommand(startWireSegmentItem->preItem,junction));
                                        }else{
                                        }
                                    }else if(firstMousePressScenePoint == startWireSegmentItem->endPoint()){
                                    }else{
                                        if(startWireSegmentItem->isHorizontalMode == wireSegmentItem->isHorizontalMode){
                                            if(startWireSegmentItem->contains(startWireSegmentItem->mapFromScene(mouseReleaseScenePoint))){
                                                cancelDrawing();
                                            }else{
                                                if(wireSegmentItem->isHorizontalMode){
                                                    const QLineF tmpLine = startWireSegmentItem->line();
                                                    if(tmpLine.p2().x() > tmpLine.p1().x()){
                                                        QLineF line = wireSegmentItem->line();
                                                        if(line.p2().x() > line.p1().x()){
                                                            line.setP1(wireSegmentItem->mapFromItem(startWireSegmentItem,tmpLine.p2()));
                                                            wireSegmentItem->setLine(line);
                                                            if(startWireSegmentItem->nextItem){
                                                                JunctionItem *junction = new JunctionItem(schScene,startWireSegmentItem->endPoint());
                                                                schScene->addItem(junction);
                                                                junction->setAttachedNet(startWireSegmentItem->attachedNet());
                                                                junction->addNextWireSegmentItem(wireSegmentItem);
                                                                preChildCommands.append(new WireSpiltCommand(startWireSegmentItem,junction));
                                                            }else{
                                                            }
                                                        }else{
                                                            line.setP1(wireSegmentItem->mapFromItem(startWireSegmentItem,tmpLine.p1()));
                                                            wireSegmentItem->setLine(line);
                                                            if(startWireSegmentItem->preItem){
                                                                JunctionItem *junction = new JunctionItem(schScene,startWireSegmentItem->startPoint());
                                                                schScene->addItem(junction);
                                                                junction->setAttachedNet(startWireSegmentItem->attachedNet());
                                                                junction->addNextWireSegmentItem(wireSegmentItem);
                                                                preChildCommands.append(new WireSpiltCommand(startWireSegmentItem->preItem,junction));
                                                            }else{
                                                            }
                                                        }
                                                    }else{
                                                    }
                                                }else{
                                                }
                                            }
                                        }else{
                                            qDebug() << "222222" ;
                                            JunctionItem *junction = new JunctionItem(schScene, firstMousePressScenePoint);
                                            schScene->addItem(junction);
                                            junction->setAttachedNet(startWireSegmentItem->attachedNet());
                                            junction->addNextWireSegmentItem(wireSegmentItem);
                                            preChildCommands.append(new WireSpiltCommand(startWireSegmentItem,junction));
                                        }
                                    }
                                }
                            }
                            break;
                            case Item::JunctionItemType: {
                                JunctionItem *junction = qgraphicsitem_cast<JunctionItem *>(item);
                                junction->addNextWireSegmentItem(wireSegmentItem);
                            }
                            break;
                        }
                    }
                    if(wireSegmentItem){
                        wire->append(wireSegmentItem);
                    }
                }else{
                    wireSegmentItem->preItem->setSelected(false);
                    //正交共线
                    if (wireSegmentItem->isHorizontalMode == wireSegmentItem->preItem->isHorizontalMode) {
                        wireSegmentItem->preItem->nextItem = wireSegmentItem->nextItem;
                        wireSegmentItem->nextItem->preItem = wireSegmentItem->preItem;

                        const QPointF endPoint = wireSegmentItem->preItem->mapFromItem(wireSegmentItem, wireSegmentItem->line().p2());
                        if (endPoint == QPointF(0, 0)) {
                            // wireSegmentItem 终点和前一段起点闭合 移除之
                            if (wireSegmentItem->preItem->preItem) {
                                wireSegmentItem->preItem->preItem->nextItem = wireSegmentItem->nextItem;
                                wireSegmentItem->nextItem->preItem = wireSegmentItem->preItem->preItem;
                                WireSegmentItem *tmpItem = wireSegmentItem;
                                wireSegmentItem = tmpItem->preItem->preItem;

                                // 移除wireSegmentItem 前一段
                                schScene->removeItem(tmpItem->preItem);
                                wire->removeLast();
                                // 移除移除wireSegmentItem
                                schScene->removeItem(tmpItem);

                                delete tmpItem->preItem;
                                delete tmpItem;
                            }
                        } else {
                            // 正常共线
                            QLineF tmpLine;
                            tmpLine.setP2(endPoint);
                            wireSegmentItem->preItem->setLine(tmpLine);
                            WireSegmentItem *tmpItem = wireSegmentItem;
                            wireSegmentItem = tmpItem->preItem;

                            schScene->removeItem(tmpItem);
                            delete tmpItem;
                        }
                    }else{
                        wire->append(wireSegmentItem);
                    }
                }

                if(wireSegmentItem){
                    // 不能先选中 否则item为控制点矩形
                    QGraphicsItem *item = schScene->itemAt(mouseReleaseScenePoint, QTransform());
                    if(item) {
                        switch(item->type()) {
                            case Item::PortItemType: {
                                PortItem *port = qgraphicsitem_cast<PortItem *>(item);
                                endDrawing(port);
                            }
                            break;
                            case Item::WireSegmentItemType: {
                                QList<QGraphicsItem *> items = schScene->items(mouseReleaseScenePoint);
                                int i = 0;
                                for (QGraphicsItem *it : items) {
                                    if (it == nextWireSegmentItem || it == wireSegmentItem || it->type() != Item::WireSegmentItemType) {
                                        items.removeAt(i);
                                    }
                                    i++;
                                }
                                if (!items.isEmpty()) {
                                    item = items.first();
                                    endWireSegmentItem = qgraphicsitem_cast<WireSegmentItem *>(item);
                                }
                            }
                            break;
                            case Item::JunctionItemType: {
                                JunctionItem *junction = qgraphicsitem_cast<JunctionItem *>(item);
                                endDrawing(junction);
                            }
                            break;
                        }
                    }
                }

                // 没有结束
                if(wireSegmentItem){
                    // 已经排除共线
                    wireSegmentItem->setSelected(true);
                    wireSegmentItem = nextWireSegmentItem;

                    nextWireSegmentItem = new WireSegmentItem(schScene);
                    nextWireSegmentItem->preItem = wireSegmentItem;
                    wireSegmentItem->nextItem = nextWireSegmentItem;
                    schScene->addItem(nextWireSegmentItem);
                }
            }
        }

        lastMouseReleaseScenePoint = mouseReleaseScenePoint;
    }

    return true;
}

bool StateWireSegmentItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent)

    if(mouseReleaseScenePoint != firstMousePressScenePoint){
        schScene->removeItem(nextWireSegmentItem);
        delete nextWireSegmentItem;
        // wireSegmentItem 最后一段可见线段
        if (wireSegmentItem->length()) {
            // 正常结束
            wireSegmentItem->preItem->setSelected(false);

            wireSegmentItem->setSelected(true);
            wireSegmentItem->nextItem = nullptr;
            wire->append(wireSegmentItem);
        } else {
            // 共线结束
            wireSegmentItem->preItem->nextItem = nullptr;

            schScene->removeItem(wireSegmentItem);
            delete wireSegmentItem;
        }

        wire->createCommandAdd();

        wireSegmentItem = nullptr;
        nextWireSegmentItem = nullptr;
        isDrawing = false;
    }

    return true;
}

bool StateWireSegmentItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *menuEvent)
{
    return true;
}

bool StateWireSegmentItem::keyPressEvent(QKeyEvent *keyEvent)
{
    return false;
}

void StateWireSegmentItem::cancelDrawing()
{
    if(isDrawing) {
        if(wire->isEmpty()){
            schScene->removeItem(wireSegmentItem);
            schScene->removeItem(nextWireSegmentItem);
            delete wireSegmentItem;
            delete nextWireSegmentItem;

            wireSegmentItem = nullptr;
            nextWireSegmentItem = nullptr;

        }else{

        }

        isDrawing = false;
    }
}

void StateWireSegmentItem::endDrawing(NodeItem *endNode)
{
    if (wireSegmentItem->preItem) {
        wireSegmentItem->preItem->setSelected(false);
    }
    // 正常结束
    if (nextWireSegmentItem->length()) {
        // 其实没有选中只是改变颜色
        wireSegmentItem->unselected();

        wireSegmentItem = nextWireSegmentItem;
        wireSegmentItem->nextItem = nullptr;
        wire->append(wireSegmentItem);
    } else {
        // 共线结束
        wireSegmentItem->nextItem = nullptr;
        schScene->removeItem(nextWireSegmentItem);
        delete nextWireSegmentItem;
    }
    wireSegmentItem->setSelected(true);

    // 放在这里是因为不确定谁是最终 wireSegmentItem
    if (endNode) {
        if (endNode->type() == Item::PortItemType) {
            PortItem *port = qgraphicsitem_cast<PortItem *>(endNode);
            port->addPreWireSegmentItem(wireSegmentItem);
        } else {
            JunctionItem *junction = qgraphicsitem_cast<JunctionItem *>(endNode);
            junction->addPreWireSegmentItem(wireSegmentItem);
        }
    }

    wire->createCommandAdd();

    wireSegmentItem = nullptr;
    nextWireSegmentItem = nullptr;
    isDrawing = false;

}

void StateWireSegmentItem::createContextMenu()
{

}
