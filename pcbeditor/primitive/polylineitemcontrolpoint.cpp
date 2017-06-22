#include "polylineitemcontrolpoint.h"
#include "polylineitem.h"
#include <QGraphicsSceneMouseEvent>

#include "pcbscene.h"

PolylineItemControlPoint::PolylineItemControlPoint(PolylineItem *parent)
    :AbstractControlPoint(parent),
      boundingItem(parent)
{
    pcbScene = boundingItem->pcbScene;
}

PolylineItemControlPoint::~PolylineItemControlPoint()
{
}

void PolylineItemControlPoint::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent);
    metaPolyline = boundingItem->polyline();
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


void PolylineItemControlPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
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

    const QPointF mouseMoveItemPoint = boundingItem->mapFromScene(mouseEvent->scenePos());
    metaPolyline.replace(flag,mouseMoveItemPoint);
    boundingItem->setPolyline(metaPolyline);
}

void PolylineItemControlPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    for (QGraphicsItem* controlPoint : boundingItem->childItems())
    {
        controlPoint->setPos(metaPolyline.at(static_cast<AbstractControlPoint *>(controlPoint)->flag));
        controlPoint->setOpacity(1);
    }
//    if(isMoved()){
//        boundingItem->metadata["geometry"] = metaPolyline;
//        boundingItem->createCommandChangeGeometry();
//        setMoved(false);
//    }
}
