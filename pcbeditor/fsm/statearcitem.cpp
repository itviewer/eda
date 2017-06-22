#include "statearcitem.h"
#include "arcitem.h"
#include "ellipseitem.h"
#include "lineitem.h"

StateArcItem::StateArcItem(QObject* parent)
    : State(parent),
      arcItem(nullptr),
      ellipseItem(nullptr),
      lineItem(nullptr),
      circleArcRadius(0),
      metaStartAngle(0)
{

}

bool StateArcItem::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        mousePressScenePoint = mouseEvent->scenePos();
        if (!ellipseItem && !arcItem)
        {
            firstMousePressScenePoint = mousePressScenePoint;
            ellipseItem = new EllipseItem(pcbScene);
            ellipseItem->setPos(firstMousePressScenePoint);
            ellipseItem->setPen(ellipseItem->normalPen);

            lineItem = new LineItem(pcbScene);
            lineItem->setPos(firstMousePressScenePoint);
            pcbScene->addItem(lineItem);

            ellipseItem->setOpacity(0.5);
            pcbScene->addItem(ellipseItem);

            circleArcPath = QPainterPath();

            isDrawing = true;
        }
    }

    return true;
}

bool StateArcItem::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (!arcItem && ellipseItem)
    {
        mouseMoveScenePoint = mouseEvent->scenePos();
        // 获得半径
        circleArcRadius = QLineF(firstMousePressScenePoint,mouseMoveScenePoint ).length();

        if (snapToGrid)
            circleArcRadius = int(circleArcRadius) - int(circleArcRadius) % 10;

        const qreal width = 2 * circleArcRadius;
        metaRect = QRectF(-circleArcRadius, -circleArcRadius,
                                          width, width);
        ellipseItem->setRect(metaRect);

        const QPointF arcStartPoint = ellipseItem->mapFromScene(mouseMoveScenePoint);
        metaStartAngle = cartesian2degree(arcStartPoint.x(), arcStartPoint.y());

        radius.setP2(1,1);
        radius.setLength(circleArcRadius);
        radius.setAngle(metaStartAngle);

        lineItem->setLine(radius);
    }
    else if (arcItem)
    {
        // 动态修改弧度
        QPainterPath tmpPath = circleArcPath;
        const QPointF ep = arcItem->mapFromScene(mouseEvent->scenePos());
        const qreal angle = cartesian2degree(ep.x(), ep.y());
        metaSweepLength = angle - metaStartAngle;
        if (metaSweepLength < 0)
        {
            metaSweepLength += 360;
        }
        // 矩形 起始角度 弧度(角度制) 这里决定弧度
        tmpPath.arcTo(metaRect, metaStartAngle, metaSweepLength);
        arcItem->setPath(tmpPath);

        radius.setAngle(angle);
        lineItem->setLine(radius);
    }

    return true;
}

bool StateArcItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (arcItem)
    {
        if (arcItem->path().length() > 5){
            pcbScene->clearSelection();
            arcItem->setSelected(true);

            arcItem->setRect(metaRect);
            arcItem->setStartAngle(metaStartAngle);
            arcItem->setSweepLength(metaSweepLength);
//            arcItem->createCommandAdd();

            arcItem = nullptr;

            metaRect = QRectF();
            metaStartAngle = 0;
            metaSweepLength = 0;
            circleArcRadius = 0;
            circleArcPath = QPainterPath();

            pcbScene->removeItem(lineItem);
            delete lineItem;
            lineItem = nullptr;
            radius = QLineF();

            isDrawing = false;
        }

    }else if (ellipseItem && !arcItem){

        if(circleArcRadius > 5){
            // 这里决定起始位置
            circleArcPath.arcMoveTo(metaRect, metaStartAngle);

            arcItem = new ArcItem(pcbScene);
            arcItem->setPos(ellipseItem->pos());
            pcbScene->addItem(arcItem);

            pcbScene->removeItem(ellipseItem);
            delete ellipseItem;
            ellipseItem = nullptr;

        }else if(mousePressScenePoint != mouseEvent->scenePos()){
            pcbScene->removeItem(ellipseItem);
            delete ellipseItem;
            ellipseItem = nullptr;

            circleArcRadius = 0;

            isDrawing = false;
        }
    }

    return true;
}

bool StateArcItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    return true;
}

bool StateArcItem::keyPressEvent(QKeyEvent *keyEvent)
{
    return false;
}

void StateArcItem::cancelDrawing()
{
    if(isDrawing){
        if(ellipseItem){
            pcbScene->removeItem(ellipseItem);
            delete ellipseItem;
            ellipseItem = nullptr;
        }

        circleArcRadius = 0;

        pcbScene->removeItem(lineItem);
        delete lineItem;
        lineItem = nullptr;
        radius = QLineF();

        isDrawing = false;
        if(arcItem){
            pcbScene->removeItem(arcItem);
            delete arcItem;
            arcItem = nullptr;

            metaRect = QRectF();
            metaStartAngle = 0;
            metaSweepLength = 0;
            circleArcPath = QPainterPath();
        }
    }
}
