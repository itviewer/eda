#include "wiresegmentitem.h"
#include "wiresegmentitemcontrolpoint.h"

#include "schematicscene.h"

#include <QGraphicsSceneMouseEvent>
#include <QToolTip>

#include "wire.h"
#include "nodeitem.h"
#include "junctionitem.h"
#include "portitem.h"

#include "wiresegmentitemremovecommand.h"
#include "wiresegmentitemmovecommand.h"
#include "wiresegmentitemchangegeometrycommand.h"

#include "wiresegmentitemprependcommand.h"
#include "wiresegmentitemappendcommand.h"
#include "wiresegmentitemmergecommand.h"

WireSegmentItem::WireSegmentItem(SchematicScene *scene, QGraphicsItem *parent)
    : QGraphicsLineItem(parent),
      AbstractShapeItem(scene, this),
      preItem(nullptr),
      nextItem(nullptr),
      attachedWire(nullptr),
      attachedStartJunction(nullptr),
      attachedEndJunction(nullptr),
      attachedStartPort(nullptr),
      attachedEndPort(nullptr),
      isHorizontalMode(true),
      isMoving(false)
{
    normalPen   = QPen(QColor(schColor.value("Display")), 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
    selectedPen = QPen(QColor(schColor.value("Selection")), 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
    drawingPen  = QPen(QColor(schColor.value("Drawing")), 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

    setAcceptHoverEvents(true);
    setPen(drawingPen);

    setFlags(ItemIsSelectable | ItemIsMovable | ItemSendsGeometryChanges | ItemIsFocusable);
    setZValue(ZValue::WireSegmentItemZValue);
}

WireSegmentItem::~WireSegmentItem()
{
}

void WireSegmentItem::selected()
{
    setZValue(ZValue::SelectedWireSegmentItemZValue);
    setPen(selectedPen);
    drawControlPoints();

//    if(attachedWire) {
//        qDebug() <<  attachedWire->count();
//    }
}

void WireSegmentItem::unselected()
{
    setZValue(ZValue::WireSegmentItemZValue);
    setPen(normalPen);
    foreach (QGraphicsItem *item, childItems()) {
        schScene->removeItem(item);
        delete item;
    }
}

int WireSegmentItem::type() const
{
    return Type;
}

qreal WireSegmentItem::length() const
{
    return line().length();
}

json &WireSegmentItem::getMetadata()
{
    // geometry在创建wire时初始化 之后通过控制点改变或undo/redo修改
    metadata["pos"] = pos();
    return metadata;
}

// 自身位置或者几何信息发生变化 产生联动
void WireSegmentItem::itemChangedHandler()
{
    if (preItem) {
        if (!preItem->isSelected()) {
            preItem->nextItemChangedHandler();
        }
    } else if (attachedStartJunction && !attachedStartJunction->isSelected()) {
        attachedStartJunction->wireSegmentItemChangedHandler(this, true);
    } else if(attachedStartPort){
        preChildCommands.append(new WireSegmentItemPrependCommand(this));
    }

    if (nextItem) {
        if (!nextItem->isSelected()) {
            nextItem->preItemChangedHandler();
        }
    } else if (attachedEndJunction &&  !attachedEndJunction->isSelected()) {
        attachedEndJunction->wireSegmentItemChangedHandler(this, false);
    } else if (attachedEndPort) {
        preChildCommands.append(new WireSegmentItemAppendCommand(this));
    }
}

void WireSegmentItem::removedHandler()
{
    if (preItem != nullptr) {
        preItem->nextItem = nullptr;
    }
    if (nextItem != nullptr) {
        nextItem->preItem = nullptr;
    }
    //    delete this;
}

void WireSegmentItem::removeItem()
{
    if (attachedWire != nullptr) {
        if (attachedWire->wireItems.size() == 1) {
            delete attachedWire;
            schScene->removeItem(this);
            delete this;
        } else {
            if (preItem == nullptr) {
                schScene->removeItem(this);
                delete this;
                attachedWire->wireItems.removeFirst();
                attachedWire->wireItems.first()->preItem = nullptr;

            } else if (nextItem == nullptr) {
                schScene->removeItem(this);
                delete this;
                attachedWire->wireItems.removeLast();
                attachedWire->wireItems.last()->nextItem = nullptr;
            } else {
                attachedWire->removeSplit(this);
            }
        }
    }
}

// 前一个item发生变化 跟随联动
void WireSegmentItem::preItemChangedHandler()
{
    QLineF tmpLine = line();
    tmpLine.setP1(mapFromItem(preItem, preItem->line().p2()));

    if (!nextItem || !nextItem->isSelected()) {
        if (isHorizontalMode) {
            tmpLine.setP2(tmpLine.p2().x(), tmpLine.p1().y());
        } else {
            tmpLine.setP2(tmpLine.p1().x(), tmpLine.p2().y());
        }
    }

    // 禁止无限传递 如果仅移动一个item则仅传递一级否则传递两级
    if (tmpLine != line()) {
        setLine(tmpLine);

        if(tmpLine.length()){
            if (nextItem && !nextItem->isSelected()) {
                nextItem->preItemChangedHandler();
            } else if (attachedEndJunction && !attachedEndJunction->isSelected()) {
                attachedEndJunction->wireSegmentItemChangedHandler(this, false);
            }
            if(mergeQueue.contains(this)){
                mergeQueue.removeOne(this);
            }
        }else{
            if(!mergeQueue.contains(this) && schScene->mouseGrabberItem()){
                mergeQueue.append(this);
            }
        }
    }
}

// 后一个item发生变化 跟随联动
void WireSegmentItem::nextItemChangedHandler()
{
    QLineF tmpLine = line();
    tmpLine.setP2(mapFromItem(nextItem, nextItem->line().p1()));

    if (!preItem || !preItem->isSelected()) {
        if (isHorizontalMode) {
            tmpLine.setP1(tmpLine.p1().x(), tmpLine.p2().y());
        } else {
            tmpLine.setP1(tmpLine.p2().x(), tmpLine.p1().y());
        }
    }

    // 禁止无限传递 如果仅移动一个item则仅传递一级否则传递两级
    if (tmpLine != line()) {
        setLine(tmpLine);

        if(tmpLine.length()){
            if (preItem && !preItem->isSelected()) {
                preItem->nextItemChangedHandler();
            } else if (attachedStartJunction && !attachedStartJunction->isSelected()) {
                attachedStartJunction->wireSegmentItemChangedHandler(this, true);
            }
            if(mergeQueue.contains(this)){
                mergeQueue.removeOne(this);
            }
        }else{
            if(!mergeQueue.contains(this) && schScene->mouseGrabberItem()){
                mergeQueue.append(this);
            }
        }
    }
}

// 前一个结点发生变化 跟随联动
void WireSegmentItem::preNodeChangedHandler(const QPointF &pos)
{
    QLineF tmpLine = line();
    const QPointF endPoint = tmpLine.p2();
    const QPointF sp = mapFromScene(pos);

    if (isHorizontalMode) {
        tmpLine.setP2(endPoint.x(), sp.y());
    } else {
        tmpLine.setP2(sp.x(), endPoint.y());
    }
    tmpLine.setP1(sp);
    setLine(tmpLine);

    if (nextItem) {
        if(!nextItem->isSelected()){
            nextItem->preItemChangedHandler();
        }
    }else if(attachedEndJunction &&  !attachedEndJunction->isSelected()){

    }else if (attachedEndPort) {
        preChildCommands.append(new WireSegmentItemAppendCommand(this));
    }
}

// 后一个结点发生变化 跟随联动
void WireSegmentItem::nextNodeChangedHandler(const QPointF &pos)
{
    QLineF tmpLine = line();
    const QPointF startPoint = tmpLine.p1();
    const QPointF ep = mapFromScene(pos);

    if (isHorizontalMode) {
        tmpLine.setP1(startPoint.x(), ep.y());
    } else {
        tmpLine.setP1(ep.x(), startPoint.y());
    }
    tmpLine.setP2(ep);
    setLine(tmpLine);

    if (preItem) {
        if(!preItem->isSelected()){
            preItem->nextItemChangedHandler();
        }
    }else if(attachedStartJunction  && !attachedStartJunction->isSelected()){

    } else if(attachedStartPort){
        preChildCommands.append(new WireSegmentItemPrependCommand(this));
    }
}

const QPointF WireSegmentItem::startPoint()
{
    return mapToScene(line().p1());
}

const QPointF WireSegmentItem::endPoint()
{
    return mapToScene(line().p2());
}

const QString WireSegmentItem::attachedNet()
{
    return attachedWire ? attachedWire->attachedNet() : "";
}

WireSegmentItem *WireSegmentItem::junctionSplit(const QPointF &pos)
{
    const QPointF splitPoint = mapFromScene(pos);
    QLineF tmpLine = line();

    QLineF newLine;
    newLine.setP2(tmpLine.p2() - splitPoint);
    WireSegmentItem *newItem = new WireSegmentItem(schScene);
    newItem->setPen(normalPen);
    newItem->setPos(pos);
    newItem->setLine(newLine);
    newItem->isHorizontalMode = isHorizontalMode;
    schScene->addItem(newItem);

    tmpLine.setP2(splitPoint);
    setLine(tmpLine);

    if(nextItem){
        nextItem->preItem = newItem;
    }
    newItem->nextItem = nextItem;
    nextItem = nullptr;

    return newItem;
}

void WireSegmentItem::createCommandRemove()
{

}

void WireSegmentItem::createCommandMove()
{
    schScene->pushCommand(new WireSegmentItemMoveCommand(this));
}

void WireSegmentItem::createCommandChangeGeometry()
{

}

QVariant WireSegmentItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
        case ItemPositionChange: {
            if (isMoving && schScene->selectedItemsCount == 1) {
                if (isHorizontalMode) {
                    return QPointF(pos().x(), value.toPointF().y());
                } else {
                    return QPointF(value.toPointF().x(), pos().y());
                }
            }
        }
        case ItemPositionHasChanged:
            // TODO 排除全选wire情况 排除新建
            if (schScene->sceneState == FSM::SelectState) {
                itemChangedHandler();
            }
            break;
        case ItemSelectedHasChanged:
            value.toBool() ? selected() : unselected() ;
            break;
//        case ItemSceneHasChanged: {
//            SchematicScene *scene = qvariant_cast<SchematicScene *> (value);
//            if (!scene) {
//                removedHandler();
//            }
//        }
//        break;
        default:
            break;
    }
    return QGraphicsItem::itemChange(change, value);
}

void WireSegmentItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsLineItem::mousePressEvent(mouseEvent);
}

void WireSegmentItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
//    for(QGraphicsItem* item:schScene->selectedItems()){
//        if(item->type() == Item::WireSegmentItemType){
//            for(QGraphicsItem* childItem:item->childItems())
//            {
//                // 不做可见性判断
//                childItem->hide();
//            }
//        }
//    }

    isMoving = true;
    QGraphicsLineItem::mouseMoveEvent(mouseEvent);
}

void WireSegmentItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (isMoved()) {
        createCommandMove();
    }
    // TODO 如果包含merge命令且自己被彻底删除，则下面执行会混乱
    QGraphicsLineItem::mouseReleaseEvent(mouseEvent);
}

void WireSegmentItem::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
        case Qt::Key_Space: {
        }
        break;
        case Qt::Key_Backspace:
        case Qt::Key_Delete: {
            removeItem();
        }
        break;
        default:
            QGraphicsLineItem::keyPressEvent(keyEvent);
            break;
    }
}

void WireSegmentItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QToolTip::showText(event->screenPos(), attachedWire->attachedNet(), event->widget());
}

void WireSegmentItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    if (QToolTip::isVisible()) {
        QToolTip::hideText();
    }
}

void WireSegmentItem::drawControlPoints()
{
    const QLineF &tmpLine = line();
    for (int i = 0; i < 2; i++) {
        WireSegmentItemControlPoint *controlPoint = new WireSegmentItemControlPoint(this);
        controlPoint->setPos(tmpLine.pointAt(i));
        controlPoint->flag = i;
    }
}
