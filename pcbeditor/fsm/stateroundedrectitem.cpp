#include "stateroundedrectitem.h"
#include "roundedrectitem.h"

#include <QtMath>

StateRoundedRectItem::StateRoundedRectItem(QObject *parent)
    : State(parent),
      rectItem(nullptr)
{
    radius = 2*designGridSize;
}

bool StateRoundedRectItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        mousePressScenePoint = mouseEvent->scenePos();
        if(!rectItem){
            firstMousePressScenePoint = mousePressScenePoint;
            rectItem = new RoundedRectItem(pcbScene);
            rectItem->setPos(firstMousePressScenePoint);

            pcbScene->addItem(rectItem);

            isDrawing = true;
        }
    }
    return true;
}

bool StateRoundedRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(rectItem){
        const QPointF rubberBandEnd = rectItem->mapFromScene(mouseEvent->scenePos());
        // 可将width和height 减一
        metaRect = QRectF(qMin(0.0, rubberBandEnd.x()), qMin(0.0, rubberBandEnd.y()),
                               qAbs(rubberBandEnd.x()) , qAbs(rubberBandEnd.y()) );

        rectItem->setRect(metaRect,radius,radius);
    }
    return true;
}

bool StateRoundedRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
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

bool StateRoundedRectItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    return true;
}

bool StateRoundedRectItem::keyPressEvent(QKeyEvent *keyEvent)
{
    return false;
}

void StateRoundedRectItem::cancelDrawing()
{
    if(isDrawing) {
        pcbScene->removeItem(rectItem);
        delete rectItem;
        rectItem = nullptr;
        isDrawing = false;
    }
}
