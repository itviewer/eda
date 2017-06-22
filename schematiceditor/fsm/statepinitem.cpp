#include "statepinitem.h"
#include "pinitem.h"
#include "defaultproperty.h"

StatePinItem::StatePinItem(QObject *parent)
    : State(parent),
      pinItem(nullptr)
{

}

bool StatePinItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        if(pinItem == nullptr){

            pinItem = new PinItem(schScene,json::parse(defaultPin)[0]);
            pinItem->setOpacity(0.3);
            pinItem->setPos(mouseEvent->scenePos());
            schScene->addItem(pinItem);

            if(schScene->focusItem()) schScene->focusItem()->clearFocus();
            pinItem->setFocus();

        }else{
            pinItem->setOpacity(1.0);
            pinItem = nullptr;
        }
    }

    return true;
}

bool StatePinItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    if(pinItem != nullptr){
        pinItem->setPos(mouseEvent->scenePos());
    }
    return true;
}

bool StatePinItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    return true;
}

bool StatePinItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    return true;
}
