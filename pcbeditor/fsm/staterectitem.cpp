#include "staterectitem.h"
#include "rectitem.h"

StateRectItem::StateRectItem(QObject *parent)
    : State(parent),
      rectItem(nullptr)
{

}

bool StateRectItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        mousePressScenePoint = mouseEvent->scenePos();
        if(!rectItem){
            firstMousePressScenePoint = mousePressScenePoint;
            rectItem = new RectItem(pcbScene);
            rectItem->setPos(firstMousePressScenePoint);

            pcbScene->addItem(rectItem);

            isDrawing = true;
        }
    }

    return true;
}

bool StateRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(rectItem){
        const QPointF rubberBandEnd = rectItem->mapFromScene(mouseEvent->scenePos());
        // 可将width和height 减一
        metaRect = QRectF(qMin(0.0, rubberBandEnd.x()), qMin(0.0, rubberBandEnd.y()),
                               qAbs(rubberBandEnd.x()) , qAbs(rubberBandEnd.y()) );

        rectItem->setRect(metaRect);
    }

    return true;
}

bool StateRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(rectItem){
        mouseReleaseScenePoint = mouseEvent->scenePos();
        // 单击 非起点且和上次单击地方不同
        if((mouseReleaseScenePoint != firstMousePressScenePoint) && (mouseReleaseScenePoint != lastMouseReleaseScenePoint)){
            // 防止误操作
            if(metaRect.width() > 5 && metaRect.height() > 5){
                pcbScene->clearSelection();
                rectItem->setSelected(true);

//                rectItem->createCommandAdd();

                rectItem = nullptr;
                metaRect = QRectF();

                isDrawing = false;
            }
        }
        lastMouseReleaseScenePoint = mouseReleaseScenePoint;
    }

    return true;
}

bool StateRectItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    return true;
}

bool StateRectItem::keyPressEvent(QKeyEvent *keyEvent)
{
    return false;
}

void StateRectItem::cancelDrawing()
{
    if(isDrawing) {
        pcbScene->removeItem(rectItem);
        delete rectItem;
        rectItem = nullptr;
        isDrawing = false;
    }
}
