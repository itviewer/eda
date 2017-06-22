#include "stateellipseitem.h"
#include "ellipseitem.h"

StateEllipseItem::StateEllipseItem(QObject *parent)
    : State(parent),
      ellipseItem(nullptr)
{
    createContextMenu();
}

bool StateEllipseItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        mousePressScenePoint = mouseEvent->scenePos();
        if(!ellipseItem){
            firstMousePressScenePoint = mousePressScenePoint;
            ellipseItem = new EllipseItem(partScene);
            ellipseItem->setPos(firstMousePressScenePoint);

            partScene->addItem(ellipseItem);

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
    if(mouseEvent->button() == Qt::LeftButton){
        mouseReleaseScenePoint = mouseEvent->scenePos();
        if(ellipseItem){
            // 单击 非起点且和上次单击地方不同
            if((mouseReleaseScenePoint != firstMousePressScenePoint) && (mouseReleaseScenePoint != lastMouseReleaseScenePoint)){
                endDrawing();
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

bool StateEllipseItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *menuEvent)
{
    actionMenuCancel->setEnabled(isDrawing);

    contextMenu->popup(menuEvent->screenPos());
    return true;
}

bool StateEllipseItem::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
        case Qt::Key_Escape: {
            cancelDrawing();
        }
    }
    return true;
}

void StateEllipseItem::cancelDrawing()
{
    if(isDrawing) {
        partScene->removeItem(ellipseItem);
        delete ellipseItem;
        ellipseItem = nullptr;
        isDrawing = false;
    }
    partEditor->setSceneState(FSM::SelectState);
}

void StateEllipseItem::endDrawing()
{
    if(isDrawing){
        // 防止误操作
        if(metaRect.width() > 5 && metaRect.height() > 5){
            partScene->clearSelection();
            ellipseItem->setSelected(true);

//            ellipseItem->createCommandAdd();

            ellipseItem = nullptr;
            metaRect = QRectF();

            isDrawing = false;
        }
    }else{
        partEditor->setSceneState(FSM::SelectState);
    }
}

void StateEllipseItem::createContextMenu()
{
    contextMenu = new QMenu;

    actionMenuEnd = contextMenu->addAction("End Drawing");
    connect(actionMenuEnd,&QAction::triggered,this,&StateEllipseItem::endDrawing);

    actionMenuCancel = contextMenu->addAction("Cancel Drawing");
    connect(actionMenuCancel,&QAction::triggered,this,&StateEllipseItem::cancelDrawing);
}
