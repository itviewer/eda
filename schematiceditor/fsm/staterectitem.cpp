#include "staterectitem.h"
#include "rectitem.h"

StateRectItem::StateRectItem(QObject *parent)
    : State(parent),
      rectItem(nullptr)
{
    createContextMenu();
}

bool StateRectItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        mousePressScenePoint = mouseEvent->scenePos();
        if(!rectItem){
            firstMousePressScenePoint = mousePressScenePoint;
            rectItem = new RectItem(schScene);
            rectItem->setPos(firstMousePressScenePoint);

            schScene->addItem(rectItem);

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
    if(mouseEvent->button() == Qt::LeftButton){
        mouseReleaseScenePoint = mouseEvent->scenePos();
        if(rectItem){
            // 单击 非起点且和上次单击地方不同
            if((mouseReleaseScenePoint != firstMousePressScenePoint) && (mouseReleaseScenePoint != lastMouseReleaseScenePoint)){
                endDrawing();
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

bool StateRectItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *menuEvent)
{
    actionMenuCancel->setEnabled(isDrawing);
    contextMenu->popup(menuEvent->screenPos());
    return true;
}

bool StateRectItem::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
        case Qt::Key_Escape: {
            cancelDrawing();
        }
    }
    return true;;
}

void StateRectItem::cancelDrawing()
{
    if(isDrawing) {
        schScene->removeItem(rectItem);
        delete rectItem;
        rectItem = nullptr;
        isDrawing = false;
    }
    schEditor->setSceneState(FSM::SelectState);
}

void StateRectItem::endDrawing()
{
    if(isDrawing){
        // 防止误操作
        if(metaRect.width() > 5 && metaRect.height() > 5){
            schScene->clearSelection();
            rectItem->setSelected(true);

            rectItem->createCommandAdd();

            rectItem = nullptr;
            metaRect = QRectF();

            isDrawing = false;
        }
    }else{
        schEditor->setSceneState(FSM::SelectState);
    }
}

void StateRectItem::createContextMenu()
{
    contextMenu = new QMenu;

    actionMenuEnd = contextMenu->addAction("End Drawing");
    connect(actionMenuEnd,&QAction::triggered,this,&StateRectItem::endDrawing);

    actionMenuCancel = contextMenu->addAction("Cancel Drawing");
    connect(actionMenuCancel,&QAction::triggered,this,&StateRectItem::cancelDrawing);
}
