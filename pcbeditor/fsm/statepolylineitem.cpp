#include "statepolylineitem.h"
#include "polylineitem.h"

StatePolylineItem::StatePolylineItem(QObject *parent)
    : State(parent),
      polylineItem(nullptr),
      isHorizontalMode(true),
      angleMode(Angle::Orthogonal)
{

}

bool StatePolylineItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        mousePressScenePoint = mouseEvent->scenePos();
        if(polylineItem == nullptr){
            firstMousePressScenePoint = mousePressScenePoint;
            polylineItem = new PolylineItem(pcbScene);
            polylineItem->setPos(firstMousePressScenePoint);
            pcbScene->addItem(polylineItem);

            metaPolyline << QPointF(0,0);

            isDrawing = true;
        }
    }

    return true;
}

bool StatePolylineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(polylineItem != nullptr){
        QPolygonF tmpPolyline = metaPolyline;
        if(angleMode == Angle::Orthogonal){
            const QPointF endPoint = polylineItem->mapFromScene(mouseEvent->scenePos());
            const QPointF lastPoint = tmpPolyline.last();
            if((endPoint.y() == lastPoint.y())){
                isHorizontalMode = true;
            }else if((endPoint.x() == lastPoint.x())){
                isHorizontalMode = false;
            }

            if(isHorizontalMode){
                orthogonalPoint.setX(endPoint.x());
                orthogonalPoint.setY(lastPoint.y());

                if(orthogonalPoint != endPoint){
                    tmpPolyline << orthogonalPoint;
                }
                tmpPolyline << endPoint;
                polylineItem->setPolyline(tmpPolyline);
            }else{
                orthogonalPoint.setX(lastPoint.x());
                orthogonalPoint.setY(endPoint.y());
                if(orthogonalPoint != endPoint){
                    tmpPolyline << orthogonalPoint;
                }
                tmpPolyline << endPoint;
                polylineItem->setPolyline(tmpPolyline);
            }
        }else{
            tmpPolyline << polylineItem->mapFromScene(mouseEvent->scenePos());
            polylineItem->setPolyline(tmpPolyline);
        }
    }

    return true;
}

bool StatePolylineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(polylineItem){
        mouseReleaseScenePoint = mouseEvent->scenePos();
        if((mouseReleaseScenePoint != firstMousePressScenePoint) && (mouseReleaseScenePoint != lastMouseReleaseScenePoint)){
            if(angleMode == Angle::Orthogonal){
                int count = metaPolyline.size();
                if(count > 1){
                    //正交模式 排除三点共线
                    const QPointF lastSecondPoint = metaPolyline.at(count - 2);
                    if((orthogonalPoint.y() == lastSecondPoint.y()) || (orthogonalPoint.x() == lastSecondPoint.x()) ){
                        metaPolyline.removeLast();
                    }
                }
                // 当前鼠标上一结点为终点算法
                metaPolyline << orthogonalPoint;
            }else{
                metaPolyline << polylineItem->mapFromScene(mousePressScenePoint);
            }
        }

        lastMouseReleaseScenePoint = mouseReleaseScenePoint;
    }
    return true;
}

bool StatePolylineItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseReleaseScenePoint != firstMousePressScenePoint){
        // 防止误操作
        if(polylineItem->path().length() > 5){
            pcbScene->clearSelection();
            polylineItem->setSelected(true);
//            polylineItem->createCommandAdd();

            polylineItem = nullptr;
            metaPolyline.clear();

            isDrawing = false;
        }
    }
    return true;
}

bool StatePolylineItem::keyPressEvent(QKeyEvent *keyEvent)
{
    return false;
}

void StatePolylineItem::cancelDrawing()
{
    if(isDrawing) {
        if(metaPolyline.size() > 1){
            pcbScene->clearSelection();
            // 重置图形
            polylineItem->setPolyline(metaPolyline);
            polylineItem->setSelected(true);

//            polylineItem->createCommandAdd();
        }else{
            pcbScene->removeItem(polylineItem);
            delete polylineItem;
        }
        polylineItem = nullptr;
        metaPolyline.clear();
        isDrawing = false;
    }
}
