#include "ellipseitemcontrolpoint.h"
#include "ellipseitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "PartScene.h"

EllipseItemControlPoint::EllipseItemControlPoint(EllipseItem *parent)
    :AbstractControlPoint(parent),
      boundingItem(parent)
{
    partScene = boundingItem->partScene;
}

EllipseItemControlPoint::~EllipseItemControlPoint()
{
}

void EllipseItemControlPoint::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent);
    metaRect = boundingItem->rect();
    boundingItem->originGeometry = boundingItem->metadata["geometry"];

    if (partScene->selectedItems().count() != 1)
    {
        for (QGraphicsItem* item : partScene->selectedItems())
        {
            if (item != parentItem())
            {
                item->setSelected(false);
            }
        }
    }
}

void EllipseItemControlPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (opacity() != 0)
    {
        for(QGraphicsItem* controlPoint : boundingItem->childItems())
        {
            controlPoint->setOpacity(0);
        }
    }

    if(!isMoved()){
        setMoved(true);
    }

    const QPointF ep = boundingItem->mapFromScene(mouseEvent->scenePos());
    QPointF mp;
    switch (flag) {
        case 0:
            mp = metaRect.bottomRight();
            break;
        case 1:
            mp = metaRect.bottomLeft();
            break;
        case 2:
            mp = metaRect.topLeft();
            break;
        case 3:
            mp = metaRect.topRight();
            break;
        default:
            break;
    }
    // 需要保留原矩形做比较 这里不能用metaRect
    QRectF rectangle = QRectF(qMin(mp.x(), ep.x()), qMin(mp.y(), ep.y()),
                           qAbs(mp.x() - ep.x()) , qAbs(mp.y() - ep.y()) );

    boundingItem->setRect(rectangle);
}

void EllipseItemControlPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    metaRect = boundingItem->rect();
    for (QGraphicsItem* controlPoint : boundingItem->childItems())
    {
        controlPoint->setPos(flagToPoint(static_cast<AbstractControlPoint *>(controlPoint)->flag,metaRect));
        controlPoint->setOpacity(1);
    }

    if(isMoved()){
        boundingItem->metadata["geometry"] = metaRect;
//        boundingItem->createCommandChangeGeometry();
        setMoved(false);
    }
//    boundingItem->updateMetadata(boundingItemPath);
}
