#include "arcitemcontrolpoint.h"
#include "arcitem.h"
#include "pcbscene.h"

ArcItemControlPoint::ArcItemControlPoint(ArcItem *parent)
    :AbstractControlPoint(parent),
      boundingItem(parent)
{
    pcbScene = boundingItem->pcbScene;
}

ArcItemControlPoint::~ArcItemControlPoint()
{
}

void ArcItemControlPoint::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent);
    boundingItemPath = boundingItem->path();
    metaRect = boundingItem->getRect();
    boundingItem->originGeometry = boundingItem->metadata["geometry"];

    if (pcbScene->selectedItems().count() != 1)
    {
        for (QGraphicsItem* item : pcbScene->selectedItems())
        {
            if (item != parentItem())
            {
                item->setSelected(false);
            }
        }
    }
}

void ArcItemControlPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(opacity() != 0){
        foreach (QGraphicsItem *controlPoint, boundingItem->childItems()) {
               controlPoint->setOpacity(0.0);
        }
    }

    if(!isMoved()){
        setMoved(true);
    }

    QPainterPath p;
    QPointF mp,ep;
    if(flag == 0){
            mp = boundingItemPath.elementAt(boundingItemPath.elementCount() - 1); // 终点
            ep = boundingItem->mapFromScene(mouseEvent->scenePos()); // 起点
    }else{
           mp = boundingItem->mapFromScene(mouseEvent->scenePos()); // 终点
           ep = boundingItemPath.elementAt(0);  // 起点
    }
    metaStartAngle = cartesian2degree(ep.x(),ep.y());
    p.arcMoveTo(metaRect,metaStartAngle);

    metaSweepLength = cartesian2degree(mp.x(),mp.y()) - metaStartAngle;
    if(metaSweepLength < 0) {
        metaSweepLength += 360;
    }
    p.arcTo(metaRect,metaStartAngle,metaSweepLength);
    boundingItem->setPath(p);
}

void ArcItemControlPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent)
    boundingItemPath = boundingItem->path();
    for (QGraphicsItem *controlPoint : boundingItem->childItems()) {
        if(static_cast<ArcItemControlPoint *>(controlPoint)->flag == 0){
            controlPoint->setPos(boundingItemPath.elementAt(0));
        }else{
            controlPoint->setPos(boundingItemPath.elementAt(boundingItemPath.elementCount() - 1));
        }
         controlPoint->setOpacity(1.0);
    }
    boundingItem->setStartAngle(metaStartAngle);
    boundingItem->setSweepLength(metaSweepLength);

    if(isMoved()){
//        boundingItem->createCommandChangeGeometry();
        setMoved(false);
    }
}

