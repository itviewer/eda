#include "polygonitemcontrolpoint.h"
#include "polygonitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "partscene.h"

PolygonItemControlPoint::PolygonItemControlPoint(PolygonItem *parent)
    :AbstractControlPoint(parent),
      boundingItem(parent)
{
    partScene = boundingItem->partScene;
}

PolygonItemControlPoint::~PolygonItemControlPoint()
{
}

void PolygonItemControlPoint::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent);
    metaPolygon = boundingItem->polygon();
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


void PolygonItemControlPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
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
    metaPolygon.replace(flag,mouseMoveItemPoint);

    // 首尾重合
//    if( flag == metaPolygon.size() - 1){
//        metaPolygon.replace(0,mouseMoveItemPoint);
//    }

    boundingItem->setPolygon(metaPolygon);
}

void PolygonItemControlPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    for (QGraphicsItem* controlPoint : boundingItem->childItems())
    {
        controlPoint->setPos(metaPolygon.at(static_cast<AbstractControlPoint *>(controlPoint)->flag));
        controlPoint->setOpacity(1);
    }

    if(isMoved()){
        boundingItem->metadata["geometry"] = metaPolygon;
//        boundingItem->createCommandChangeGeometry();
        setMoved(false);
    }
}
