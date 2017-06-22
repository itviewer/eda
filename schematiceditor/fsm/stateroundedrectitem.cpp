#include "stateroundedrectitem.h"
#include "roundedrectitem.h"

StateRoundedRectItem::StateRoundedRectItem(QObject *parent)
    : State(parent),
      rectItem(nullptr)
{
    radius = 2*designGridSize;
    createContextMenu();
}

bool StateRoundedRectItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        mousePressScenePoint = mouseEvent->scenePos();
        if(!rectItem){
            firstMousePressScenePoint = mousePressScenePoint;
            rectItem = new RoundedRectItem(schScene);
            rectItem->setPos(firstMousePressScenePoint);

            schScene->addItem(rectItem);

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

bool StateRoundedRectItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    return true;
}

bool StateRoundedRectItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *menuEvent)
{
    actionMenuCancel->setEnabled(isDrawing);

    contextMenu->popup(menuEvent->screenPos());
    return true;
}

bool StateRoundedRectItem::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
        case Qt::Key_Escape: {
            cancelDrawing();
        }
    }
    return true;
}

void StateRoundedRectItem::cancelDrawing()
{
    if(isDrawing) {
        schScene->removeItem(rectItem);
        delete rectItem;
        rectItem = nullptr;
        isDrawing = false;
    }
    schEditor->setSceneState(FSM::SelectState);
}

void StateRoundedRectItem::endDrawing()
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

void StateRoundedRectItem::createContextMenu()
{
    contextMenu = new QMenu;

    actionMenuEnd = contextMenu->addAction("End Drawing");
    connect(actionMenuEnd,&QAction::triggered,this,&StateRoundedRectItem::endDrawing);

    actionMenuCancel = contextMenu->addAction("Cancel Drawing");
    connect(actionMenuCancel,&QAction::triggered,this,&StateRoundedRectItem::cancelDrawing);
}
