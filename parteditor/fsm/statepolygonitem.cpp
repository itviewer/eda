#include "statepolygonitem.h"
#include "polygonitem.h"

StatePolygonItem::StatePolygonItem(QObject *parent)
    : State(parent),
      polygonItem(nullptr),
      isHorizontalMode(true),
      isOrthogonalMode(true)
{
    createContextMenu();
}

bool StatePolygonItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        mousePressScenePoint = mouseEvent->scenePos();
        if(polygonItem == nullptr){
            firstMousePressScenePoint = mousePressScenePoint;
            polygonItem = new PolygonItem(partScene);
            polygonItem->setPos(firstMousePressScenePoint);
            partScene->addItem(polygonItem);

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
    if(mouseEvent->button() == Qt::LeftButton){
        mouseReleaseScenePoint = mouseEvent->scenePos();
        if(polygonItem){
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
        }
        lastMouseReleaseScenePoint = mouseReleaseScenePoint;
    }
    return true;
}


bool StatePolygonItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() == Qt::LeftButton){
        if(mouseReleaseScenePoint != firstMousePressScenePoint){
            endDrawing();
        }
    }
    return true;
}

bool StatePolygonItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *menuEvent)
{
    actionMenuCancel->setEnabled(isDrawing);

    contextMenu->popup(menuEvent->screenPos());
    return true;
}

bool StatePolygonItem::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
        case Qt::Key_Escape: {
            cancelDrawing();
        }
    }
    return true;
}

void StatePolygonItem::cancelDrawing()
{
    if(isDrawing) {
        if(metaPolygon.size() > 1){
            partScene->clearSelection();
            polygonItem->setSelected(true);

//            polygonItem->createCommandAdd();
        }else{
            partScene->removeItem(polygonItem);
            delete polygonItem;
        }
        polygonItem = nullptr;
        metaPolygon.clear();
        isDrawing = false;
    }
    partEditor->setSceneState(FSM::SelectState);
}

void StatePolygonItem::endDrawing()
{
    if(isDrawing){
        // 防止误操作
        if(polygonItem->path().length() > 5){
            partScene->clearSelection();
            polygonItem->setSelected(true);
//            polygonItem->createCommandAdd();

            polygonItem = nullptr;
            metaPolygon.clear();

            isDrawing = false;
        }
    }else{
        partEditor->setSceneState(FSM::SelectState);
    }
}

void StatePolygonItem::createContextMenu()
{
    contextMenu = new QMenu;

    actionMenuEnd = contextMenu->addAction("End Drawing");
    connect(actionMenuEnd,&QAction::triggered,this,&StatePolygonItem::endDrawing);

    actionMenuCancel = contextMenu->addAction("Cancel Drawing");
    connect(actionMenuCancel,&QAction::triggered,this,&StatePolygonItem::cancelDrawing);
}
