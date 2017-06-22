#include "statelineitem.h"
#include "lineitem.h"

StateLineItem::StateLineItem(QObject *parent)
    : State(parent),
      lineItem(nullptr)
{
}

bool StateLineItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() == Qt::LeftButton) {
        mousePressScenePoint = mouseEvent->scenePos();
        if(!lineItem) {
            firstMousePressScenePoint = mousePressScenePoint;
            lineItem = new LineItem(pcbScene);
            lineItem->setPos(firstMousePressScenePoint);

            pcbScene->addItem(lineItem);

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
    if(lineItem) {
        mouseReleaseScenePoint = mouseEvent->scenePos();
        // 单击 非起点且和上次单击地方不同
        if((mouseReleaseScenePoint != firstMousePressScenePoint) && (mouseReleaseScenePoint != lastMouseReleaseScenePoint)) {

            // 防止误操作
            if(lineItem->line().length() > 5) {
                pcbScene->clearSelection();
                lineItem->setSelected(true);
//                lineItem->createCommandAdd();

                lineItem = nullptr;
                metaLine = QLineF();

                isDrawing = false;
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

// 不阻塞键盘事件
bool StateLineItem::keyPressEvent(QKeyEvent *keyEvent)
{
//    switch (keyEvent->key()) {
//        case Qt::Key_Escape: {
//            cancelDrawing();
//        }
//    }
    return false;
}

void StateLineItem::cancelDrawing()
{
    if(isDrawing) {
        pcbScene->removeItem(lineItem);
        delete lineItem;
        lineItem = nullptr;
        isDrawing = false;
    }
}
