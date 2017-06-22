#include "lineitemcontrolpoint.h"
#include "lineitem.h"
#include "schematicscene.h"

LineItemControlPoint::LineItemControlPoint(LineItem* parent)
    : AbstractControlPoint(parent),
      boundingItem(parent)
{
    schScene = boundingItem->schScene;
}

LineItemControlPoint::~LineItemControlPoint()
{
}

void LineItemControlPoint::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    Q_UNUSED(mouseEvent);
    metaLine = boundingItem->line();
    boundingItem->originGeometry = boundingItem->metadata["geometry"];

    if (schScene->selectedItems().count() != 1)
    {
        for (QGraphicsItem* item : schScene->selectedItems())
        {
            if (item != parentItem())
            {
                item->setSelected(false);
            }
        }
    }
}

void LineItemControlPoint::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
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

    const QPointF mousePressItemPoint = boundingItem->mapFromScene(mouseEvent->scenePos());
    flag ? metaLine.setP2(mousePressItemPoint) : metaLine.setP1(mousePressItemPoint);
    boundingItem->setLine(metaLine);

}

void LineItemControlPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    for (QGraphicsItem* controlPoint : boundingItem->childItems())
    {
        controlPoint->setPos(metaLine.pointAt(static_cast<AbstractControlPoint *>(controlPoint)->flag));
        controlPoint->setOpacity(1);
    }

    if(isMoved()){
        boundingItem->metadata["geometry"] = metaLine;
        boundingItem->createCommandChangeGeometry();
        setMoved(false);
    }
//    boundingItem->updateMetadata(metaLine);
}
