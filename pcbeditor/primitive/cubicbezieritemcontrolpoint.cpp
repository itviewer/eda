#include "cubicbezieritemcontrolpoint.h"
#include "cubicbezieritem.h"

#include "pcbscene.h"

CubicBezierItemControlPoint::CubicBezierItemControlPoint(CubicBezierItem *parent)
    :AbstractControlPoint(parent),
      boundingItem(parent)
{
    pcbScene = boundingItem->pcbScene;
}

CubicBezierItemControlPoint::~CubicBezierItemControlPoint()
{

}


void CubicBezierItemControlPoint::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent);
    metaPolygon = boundingItem->getPolygon();
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

void CubicBezierItemControlPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(opacity() != 0){
        foreach (QGraphicsItem *controlPoint, boundingItem->childItems()) {
               controlPoint->setOpacity(0.0);
        }
    }

    if(!isMoved()){
        setMoved(true);
    }

    metaPolygon.replace(flag,boundingItem->mapFromScene(mouseEvent->scenePos()));
    QPainterPath tmpPath(metaPolygon.first());

    int size = metaPolygon.size() - 1;
    for(int i = 0; i < size;i+=3){
        tmpPath.cubicTo(metaPolygon.at(i+1),metaPolygon.at(i+2),metaPolygon.at(i+3));
    }
    boundingItem->setPath(tmpPath);
}

void CubicBezierItemControlPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent);
    for (QGraphicsItem* controlPoint : boundingItem->childItems())
    {
        controlPoint->setPos(metaPolygon.at(static_cast<AbstractControlPoint *>(controlPoint)->flag));
        controlPoint->setOpacity(1);
    }
    if(isMoved()){
        boundingItem->setPolygon(metaPolygon);
        boundingItem->metadata["geometry"] = metaPolygon;
//        boundingItem->createCommandChangeGeometry();
        setMoved(false);
    }

}
