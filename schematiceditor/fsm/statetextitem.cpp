#include "statetextitem.h"
#include "textitem.h"

StateTextItem::StateTextItem(QObject *parent)
    : State(parent),
      textItem(nullptr)
{

}

bool StateTextItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        if(textItem == nullptr){
            textItem = new TextItem(schScene,"这时测试");
            textItem->setPos(mouseEvent->scenePos());

            schScene->addItem(textItem);
            textItem->setSelected(true);
        }
    }

    return true;
}

bool StateTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    return true;
}

bool StateTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    textItem->createCommandAdd();
    textItem = nullptr;
    return true;
}

bool StateTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    return true;
}

bool StateTextItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *menuEvent)
{
    return true;
}

bool StateTextItem::keyPressEvent(QKeyEvent *keyEvent)
{
    return false;
}

void StateTextItem::cancelDrawing()
{

}
