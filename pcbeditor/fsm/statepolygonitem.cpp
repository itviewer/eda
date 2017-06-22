#include "statepolygonitem.h"
#include "polygonitem.h"

StatePolygonItem::StatePolygonItem(QObject *parent)
    : State(parent),
      polygonItem(nullptr),
      isHorizontalMode(true),
      isOrthogonalMode(true)
{

}

bool StatePolygonItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        mousePressScenePoint = mouseEvent->scenePos();
        if(polygonItem == nullptr){
            firstMousePressScenePoint = mousePressScenePoint;
            polygonItem = new PolygonItem(pcbScene);
            polygonItem->setPos(firstMousePressScenePoint);
            pcbScene->addItem(polygonItem);

            metaPolygon << QPointF(0,0);

            isDrawing = true;
        }
    }

    return true;
}

bool StatePolygonItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(polygonItem != nullptr){
        QPolygonF tmpPolygon = metaPolygon;
        if(isOrthogonalMode){
            const QPointF endPoint = polygonItem->mapFromScene(mouseEvent->scenePos());
            const QPointF lastPoint = tmpPolygon.last();
            if((endPoint.y() == lastPoint.y())){
                isHorizontalMode = true;
            }else if((endPoint.x() == lastPoint.x())){
                isHorizontalMode = false;
            }

            if(isHorizontalMode){
                orthogonalPoint.setX(endPoint.x());
                orthogonalPoint.setY(lastPoint.y());

                if(orthogonalPoint != endPoint){
                    tmpPolygon << orthogonalPoint;
                }
                tmpPolygon << endPoint;
                polygonItem->setPolygon(tmpPolygon);
            }else{
                orthogonalPoint.setX(lastPoint.x());
                orthogonalPoint.setY(endPoint.y());
                if(orthogonalPoint != endPoint){
                    tmpPolygon << orthogonalPoint;
                }
                tmpPolygon << endPoint;
                polygonItem->setPolygon(tmpPolygon);
            }
        }else{
            tmpPolygon << polygonItem->mapFromScene(mouseEvent->scenePos());
            polygonItem->setPolygon(tmpPolygon);
        }
    }

    return true;
}

bool StatePolygonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(polygonItem){
        mouseReleaseScenePoint = mouseEvent->scenePos();
        if((mouseReleaseScenePoint != firstMousePressScenePoint) && (mouseReleaseScenePoint != lastMouseReleaseScenePoint)){
            if(isOrthogonalMode){
                int count = metaPolygon.size();
                if(count > 1){
                    //正交模式 排除三点共线
                    const QPointF lastSecondPoint = metaPolygon.at(count - 2);
                    if((orthogonalPoint.y() == lastSecondPoint.y()) || (orthogonalPoint.x() == lastSecondPoint.x()) ){
                        metaPolygon.removeLast();
                    }
                }
                // 当前鼠标上一结点为终点算法
                metaPolygon << orthogonalPoint;
            }else{
                metaPolygon << polygonItem->mapFromScene(mousePressScenePoint);
            }
        }

        lastMouseReleaseScenePoint = mouseReleaseScenePoint;
    }
    return true;
}


bool StatePolygonItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseReleaseScenePoint != firstMousePressScenePoint){
        // 防止误操作
        if(polygonItem->path().length() > 5){
            pcbScene->clearSelection();
            polygonItem->setSelected(true);
//            polygonItem->createCommandAdd();

            polygonItem = nullptr;
            metaPolygon.clear();

            isDrawing = false;
        }
    }

    return true;
}

bool StatePolygonItem::keyPressEvent(QKeyEvent *keyEvent)
{
    return false;
}

void StatePolygonItem::cancelDrawing()
{
    if(isDrawing) {
        if(metaPolygon.size() > 1){
            pcbScene->clearSelection();
            polygonItem->setSelected(true);

//            polygonItem->createCommandAdd();
        }else{
            pcbScene->removeItem(polygonItem);
            delete polygonItem;
        }
        polygonItem = nullptr;
        metaPolygon.clear();
        isDrawing = false;
    }
}
