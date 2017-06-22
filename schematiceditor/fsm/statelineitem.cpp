#include "statelineitem.h"
#include "lineitem.h"

StateLineItem::StateLineItem(QObject *parent)
    : State(parent),
      lineItem(nullptr)
{
    createContextMenu();
}

bool StateLineItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() == Qt::LeftButton) {
        mousePressScenePoint = mouseEvent->scenePos();
        if(!lineItem) {
            firstMousePressScenePoint = mousePressScenePoint;
            lineItem = new LineItem(schScene);
            lineItem->setPos(firstMousePressScenePoint);

            schScene->addItem(lineItem);

            isDrawing = true;
        }
    }
    return true;
}

bool StateLineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(lineItem) {
        metaLine.setP2(lineItem->mapFromScene(mouseEvent->scenePos()));
        lineItem->setLine(metaLine);
    }
    return true;
}

bool StateLineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() == Qt::LeftButton){
        mouseReleaseScenePoint = mouseEvent->scenePos();
        if(lineItem) {
            // 单击 非起点且和上次单击地方不同
            if((mouseReleaseScenePoint != firstMousePressScenePoint) && (mouseReleaseScenePoint != lastMouseReleaseScenePoint)) {
                endDrawing();
            }
        }
        lastMouseReleaseScenePoint = mouseReleaseScenePoint;
    }
    return true;
}

bool StateLineItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    return true;
}

bool StateLineItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *menuEvent)
{

    actionMenuCancel->setEnabled(isDrawing);

    contextMenu->popup(menuEvent->screenPos());
    return true;
}

// 不阻塞键盘事件
bool StateLineItem::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
        case Qt::Key_Escape: {
            cancelDrawing();
        }
    }
    return true;
}

void StateLineItem::cancelDrawing()
{
    if(isDrawing) {
        schScene->removeItem(lineItem);
        delete lineItem;
        lineItem = nullptr;
        isDrawing = false;
    }
    schEditor->setSceneState(FSM::SelectState);
}

void StateLineItem::endDrawing()
{
    if(isDrawing) {
        // 防止误操作
        if(lineItem->line().length() > 5) {
            schScene->clearSelection();
            lineItem->setSelected(true);
            lineItem->createCommandAdd();

            lineItem = nullptr;
            metaLine = QLineF();

            isDrawing = false;
        }
    }else{
        schEditor->setSceneState(FSM::SelectState);
    }
}

void StateLineItem::createContextMenu()
{
    contextMenu = new QMenu;

    actionMenuEnd = contextMenu->addAction("End Drawing");
    connect(actionMenuEnd,&QAction::triggered,this,&StateLineItem::endDrawing);

    actionMenuCancel = contextMenu->addAction("Cancel Drawing");
    connect(actionMenuCancel,&QAction::triggered,this,&StateLineItem::cancelDrawing);
}
