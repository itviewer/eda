#include "wiresegmentitemcontrolpoint.h"
#include "wiresegmentitem.h"
#include "schematicscene.h"
#include "global.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

WireSegmentItemControlPoint::WireSegmentItemControlPoint(WireSegmentItem *parent)
    :AbstractControlPoint(parent),
      boundingItem(parent)
{
    schScene = boundingItem->schScene;
}

WireSegmentItemControlPoint::~WireSegmentItemControlPoint()
{
}

void WireSegmentItemControlPoint::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent);
    metaLine = boundingItem->line();
    boundingItem->originGeometry = boundingItem->metadata["geometry"];

    if(schScene->selectedItemsCount != 1){
        // 不能使用 clearSelection()
        for(QGraphicsItem *item:schScene->selectedItems()){
            if(item != boundingItem){
                item->setSelected(false);
            }
        }
    }

    if(flag == 0 && boundingItem->preItem){
        boundingItem->preItem->setSelected(true);
    }
    if(flag == 1 && boundingItem->nextItem){
        boundingItem->nextItem->setSelected(true);
    }
}

void WireSegmentItemControlPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(opacity() != 0){
        for (QGraphicsItem *controlPoint:boundingItem->childItems()) {
               controlPoint->setOpacity(0);
        }
        if(boundingItem->preItem && boundingItem->preItem->isSelected()){
            for (QGraphicsItem *controlPoint:boundingItem->preItem->childItems()) {
                   controlPoint->setOpacity(0);
            }
        }
        if(boundingItem->nextItem && boundingItem->nextItem->isSelected()){
            for (QGraphicsItem *controlPoint:boundingItem->nextItem->childItems()) {
                   controlPoint->setOpacity(0);
            }
        }
    }

    if(!isMoved()){
        setMoved(true);
    }

    if(flag == 0){
        const QPointF sp = boundingItem->mapFromScene(mouseEvent->scenePos());
        const QPointF endPoint = metaLine.p2();
        // ep 等于 endPoint 时 boundingItem 不能被隐藏 否则控制点失效
        if(sp != endPoint){
            if(boundingItem->isHorizontalMode){
                metaLine.setP2(endPoint.x(),sp.y());
            }else{
                metaLine.setP2(sp.x(),endPoint.y());
            }
            metaLine.setP1(sp);
            boundingItem->setLine(metaLine);
            // 仅修改后面
            boundingItem->itemChangedHandler();

            if(boundingItem->preItem){
                const QPointF ep = boundingItem->preItem->mapFromScene(mouseEvent->scenePos());
                const QPointF startPoint = boundingItem->preItem->line().p1();
                if(boundingItem->preItem->isHorizontalMode){
                    tmpLine.setP1(startPoint.x(),ep.y());
                }else{
                    tmpLine.setP1(ep.x(),startPoint.y());
                }
                tmpLine.setP2(ep);
                boundingItem->preItem->setLine(tmpLine);
                // 仅修改前面
                boundingItem->preItem->itemChangedHandler();
            }
        }
    }else{
        const QPointF ep = boundingItem->mapFromScene(mouseEvent->scenePos());
        const QPointF startPoint = metaLine.p1();
        if(ep != startPoint){
            if(boundingItem->isHorizontalMode){
                metaLine.setP1(startPoint.x(),ep.y());
            }else{
                metaLine.setP1(ep.x(),startPoint.y());
            }
            metaLine.setP2(ep);
            boundingItem->setLine(metaLine);
            // 仅修改前面
            boundingItem->itemChangedHandler();

            if(boundingItem->nextItem){
                const QPointF sp = boundingItem->nextItem->mapFromScene(mouseEvent->scenePos());
                const QPointF endPoint = boundingItem->nextItem->line().p2();
                if(boundingItem->nextItem->isHorizontalMode){
                    tmpLine.setP2(endPoint.x(),sp.y());
                }else{
                    tmpLine.setP2(sp.x(),endPoint.y());
                }
                tmpLine.setP1(sp);
                boundingItem->nextItem->setLine(tmpLine);
                // 仅修改后面
                boundingItem->nextItem->itemChangedHandler();
            }
        }
    }
}

// TODO 鼠标释放时检查 关联节点是否隐藏,如有则更改前后关系并删除
void WireSegmentItemControlPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent);
    for (QGraphicsItem* controlPoint : boundingItem->childItems())
    {
        controlPoint->setPos(metaLine.pointAt(static_cast<AbstractControlPoint *>(controlPoint)->flag));
        controlPoint->setOpacity(1);
    }
    if(boundingItem->preItem && boundingItem->preItem->isSelected()){
        for (QGraphicsItem *controlPoint:boundingItem->preItem->childItems()) {
            controlPoint->setPos(boundingItem->preItem->line().pointAt(static_cast<AbstractControlPoint *>(controlPoint)->flag));
            controlPoint->setOpacity(1);
        }
    }
    if(boundingItem->nextItem && boundingItem->nextItem->isSelected()){
        for (QGraphicsItem *controlPoint:boundingItem->nextItem->childItems()) {
            controlPoint->setPos(boundingItem->nextItem->line().pointAt(static_cast<AbstractControlPoint *>(controlPoint)->flag));
            controlPoint->setOpacity(1);
        }
    }

    if(isMoved()){
        boundingItem->metadata["geometry"] = metaLine;
        boundingItem->createCommandChangeGeometry();
        setMoved(false);
    }
}
