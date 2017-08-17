#include "stateviaitem.h"
#include "paditem.h"

StateViaItem::StateViaItem(QObject *parent)
    : State(parent)
{

}

bool StateViaItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    json j = R"(
             {
                 "pos":[0,0],
                 "rotation":0,
                 "type":0,
                 "geometry":{
                     "size":[20,20],
                     "hole":10
                 }
             }
             )"_json;

    PadItem *pad = new PadItem(pcbScene,j);
    pad->setPos(mouseEvent->scenePos());
    pcbScene->addItem(pad);
    return true;
}

bool StateViaItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    return true;
}

bool StateViaItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    return true;
}

bool StateViaItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    return true;
}

bool StateViaItem::keyPressEvent(QKeyEvent *keyEvent)
{
    return false;
}

void StateViaItem::cancelDrawing()
{

}
