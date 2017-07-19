#include "statepinitem.h"
#include "pinitem.h"
#include "defaultproperty.h"

StatePinItem::StatePinItem(QObject *parent)
    : State(parent),
      pinItem(nullptr)
{

}

void StatePinItem::onEntry(PartScene *scene)
{
    State::onEntry(scene);
    if(!pinItem) {
        pinItem = new PinItem(partScene, json::parse(defaultPin)[0], partScene->aideRectItem);

    }
    aideRect = partScene->aideRectItem->rect();
    aspectRatio = aideRect.height() / aideRect.width();
    topLine.setPoints(aideRect.topLeft(), aideRect.topRight());
    rightLine.setPoints(aideRect.topRight(), aideRect.bottomRight());
    bottomLine.setPoints(aideRect.bottomLeft(), aideRect.bottomRight());
    leftLine.setPoints(aideRect.topLeft(), aideRect.bottomLeft());
}

bool StatePinItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
//    if(mouseEvent->button() == Qt::LeftButton) {
//    }
    return true;
}

bool StatePinItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(pinItem) {
        const QPointF ep = partScene->aideRectItem->mapFromScene(mouseEvent->scenePos());
        const QPointF tep = ep - aideRect.center();
        const qreal x = tep.x();
        const qreal y = tep.y();
        const QLineF line(aideRect.center(), ep);

        QPointF intersectionPoint;

        if(x > 0) {
            if(y > 0) {
                if(qAbs(y / x) >= aspectRatio) {
                    line.intersect(bottomLine, &intersectionPoint);
                    pinItem->setRotation(90);
                    pinItem->setPos(intersectionPoint);
                    qDebug() << "bottom" << intersectionPoint ;

                } else {
                    line.intersect(rightLine, &intersectionPoint);
                    pinItem->setRotation(0);
                    pinItem->setPos(intersectionPoint);
                    qDebug() << "right"  << intersectionPoint ;
                }
            } else if(y < 0) {
                if(qAbs(y / x) >= aspectRatio) {
                    line.intersect(topLine, &intersectionPoint);
                    pinItem->setRotation(-90);
                    pinItem->setPos(intersectionPoint);
                    qDebug() << "top"  << intersectionPoint ;
                } else {
                    line.intersect(rightLine, &intersectionPoint);
                    pinItem->setRotation(0);
                    pinItem->setPos(intersectionPoint);
                    qDebug() << "right"  << intersectionPoint ;
                }
            } else {

            }
        } else if(x < 0) {
            if(y > 0) {
                if(qAbs(y / x) >= aspectRatio) {
                    line.intersect(bottomLine, &intersectionPoint);
                    pinItem->setRotation(90);
                    pinItem->setPos(intersectionPoint);
                    qDebug() << "bottom"  << intersectionPoint ;
                } else {
                    line.intersect(leftLine, &intersectionPoint);
                    pinItem->setRotation(180);
                    pinItem->setPos(intersectionPoint);
                    qDebug() << "left"  << intersectionPoint ;
                }
            } else if(y < 0) {
                if(qAbs(y / x) >= aspectRatio) {
                    line.intersect(topLine, &intersectionPoint);
                    pinItem->setRotation(-90);
                    pinItem->setPos(intersectionPoint);
                    qDebug() << "top"  << intersectionPoint ;
                } else {
                    line.intersect(leftLine, &intersectionPoint);
                    pinItem->setRotation(180);
                    pinItem->setPos(intersectionPoint);
                    qDebug() << "left"  << intersectionPoint ;
                }
            } else {

            }
        } else {

        }
    }

    return true;
}

bool StatePinItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() == Qt::LeftButton) {
        pinItem = nullptr;
        if(!pinItem) {
            pinItem = new PinItem(partScene, json::parse(defaultPin)[0], partScene->aideRectItem);
            pinItem->setPos(partScene->aideRectItem->mapFromScene(mouseEvent->scenePos()));
        }
    }
    return true;
}

bool StatePinItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    return true;
}
