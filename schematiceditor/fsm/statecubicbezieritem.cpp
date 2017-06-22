#include "statecubicbezieritem.h"
#include "cubicbezieritem.h"

StateCubicBezierItem::StateCubicBezierItem(QObject *parent)
    : State(parent),
      bezierItem(nullptr)
{
    createContextMenu();
}

bool StateCubicBezierItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        mousePressScenePoint = mouseEvent->scenePos();
        if(!bezierItem){
            firstMousePressScenePoint = mousePressScenePoint;

            bezierItem = new CubicBezierItem(schScene);
            bezierItem->setPos(firstMousePressScenePoint);
            schScene->addItem(bezierItem);

            cPoint1 = cPoint2 = QPointF(0,0);
            metaPolygon << cPoint1;
            bezierPath.moveTo(QPointF(0,0));
            flag = 0;

            isDrawing = true;
        }
    }
    return true;
}

bool StateCubicBezierItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(bezierItem){
        QPainterPath tmpPath = bezierPath;
        ep = bezierItem->mapFromScene(mouseEvent->scenePos());
        if(flag == 1) cPoint2 = ep;
        tmpPath.cubicTo(cPoint1,cPoint2,ep);
        bezierItem->setPath(tmpPath);
    }
    return true;
}

bool StateCubicBezierItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton){
        mouseReleaseScenePoint = mouseEvent->scenePos();
        if(bezierItem){
            if((mouseReleaseScenePoint != firstMousePressScenePoint) && (mouseReleaseScenePoint != lastMouseReleaseScenePoint)){
                switch (flag) {
                    case 0:
                        cPoint1 = ep;
                        metaPolygon << cPoint1;
                        flag += 1;
                        break;
                    case 1:
                        cPoint2 = ep;
                        metaPolygon << cPoint2;
                        flag += 1;
                        break;
                    case 2:
                        // 三次不同点击处产生的长度肯定满足最小长度
                        bezierPath.cubicTo(cPoint1,cPoint2,ep);
                        cPoint1 = ep;
                        cPoint2 = ep;
                        metaPolygon << ep;
                        flag = 0;
                        break;
                }
            }
        }
        lastMouseReleaseScenePoint = mouseReleaseScenePoint;
    }
    return true;
}

bool StateCubicBezierItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton){
        if(mouseReleaseScenePoint != firstMousePressScenePoint){
            endDrawing();
        }
    }
    return true;
}

bool StateCubicBezierItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *menuEvent)
{
    actionMenuCancel->setEnabled(isDrawing);

    contextMenu->popup(menuEvent->screenPos());
    return true;
}

bool StateCubicBezierItem::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
        case Qt::Key_Escape: {
            cancelDrawing();
        }
    }
    return true;
}

// TODO　cancelDrawing和endDrawing混了
void StateCubicBezierItem::cancelDrawing()
{
    if (isDrawing) {
        if(bezierItem->path().length() > 5){
            schScene->clearSelection();
            switch (flag) {
                case 0:
                    if(metaPolygon.last() != ep){
                        metaPolygon << ep << ep << ep;
                    }
                    break;
                case 1:
                    metaPolygon << ep << ep;// cPoint1 cPoint2 等于ep
                    break;
                case 2:
                    metaPolygon << ep;// cPoint2 等于ep
                    break;
            }
            bezierItem->setPolygon(metaPolygon);
            bezierItem->setSelected(true);
            bezierItem->createCommandAdd();
        }else{
            schScene->removeItem(bezierItem);
            delete bezierItem;
        }
        bezierItem = nullptr;
        metaPolygon.clear();
        bezierPath = QPainterPath();

        isDrawing = false;
    }
    schEditor->setSceneState(FSM::SelectState);
}

void StateCubicBezierItem::endDrawing()
{
    if(isDrawing){
        // 防止误操作
        if(bezierItem->path().length() > 5){
            schScene->clearSelection();
            switch (flag) {
                case 0:
                    break;
                case 1:
                    metaPolygon << ep << ep;// cPoint1 cPoint2 等于ep
                    break;
                case 2:
                    metaPolygon << ep;// cPoint2 等于ep
                    break;
            }
            bezierItem->setPolygon(metaPolygon);
            bezierItem->setSelected(true);
            bezierItem->createCommandAdd();

            bezierItem = nullptr;
            metaPolygon.clear();
            bezierPath = QPainterPath();

            isDrawing = false;
        }
    }else{
        schEditor->setSceneState(FSM::SelectState);
    }
}

void StateCubicBezierItem::createContextMenu()
{
    contextMenu = new QMenu;

    actionMenuEnd = contextMenu->addAction("End Drawing");
    connect(actionMenuEnd,&QAction::triggered,this,&StateCubicBezierItem::endDrawing);

    actionMenuCancel = contextMenu->addAction("Cancel Drawing");
    connect(actionMenuCancel,&QAction::triggered,this,&StateCubicBezierItem::cancelDrawing);
}
