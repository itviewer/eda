#include "stateellipseitem.h"
#include "ellipseitem.h"

StateEllipseItem::StateEllipseItem(QObject *parent)
    : State(parent),
      ellipseItem(nullptr)
{

}

bool StateEllipseItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        mousePressScenePoint = mouseEvent->scenePos();
        if(!ellipseItem){
            firstMousePressScenePoint = mousePressScenePoint;
            ellipseItem = new EllipseItem(pcbScene);
            ellipseItem->setPos(firstMousePressScenePoint);

            pcbScene->addItem(ellipseItem);

            isDrawing = true;
        }
    }

    return true;
}

bool StateEllipseItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(ellipseItem != nullptr){
        const QPointF rubberBandEnd = ellipseItem->mapFromScene(mouseEvent->scenePos());
        // 可将width和height 减一
        metaRect = QRectF(qMin(0.0, rubberBandEnd.x()), qMin(0.0, rubberBandEnd.y()),
                               qAbs(rubberBandEnd.x()) , qAbs(rubberBandEnd.y()) );
        ellipseItem->setRect(metaRect);
    }
    return true;
}

bool StateEllipseItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(ellipseItem){
        mouseReleaseScenePoint = mouseEvent->scenePos();
        // 单击 非起点且和上次单击地方不同
        if((mouseReleaseScenePoint != firstMousePressScenePoint) && (mouseReleaseScenePoint != lastMouseReleaseScenePoint)){
            // 防止误操作
            if(metaRect.width() > 5 && metaRect.height() > 5){
                pcbScene->clearSelection();
                ellipseItem->setSelected(true);

//                ellipseItem->createCommandAdd();

                ellipseItem = nullptr;
                metaRect = QRectF();

                isDrawing = false;
            }
        }
        lastMouseReleaseScenePoint = mouseReleaseScenePoint;
    }
    return true;
}

bool StateEllipseItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    return true;
}

bool StateEllipseItem::keyPressEvent(QKeyEvent *keyEvent)
{
    return false;
}

void StateEllipseItem::cancelDrawing()
{
    if(isDrawing) {
        pcbScene->removeItem(ellipseItem);
        delete ellipseItem;
        ellipseItem = nullptr;
        isDrawing = false;
    }
}
