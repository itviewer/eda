#include "statepixmapitem.h"
#include "pixmapitem.h"

StatePixmapItem::StatePixmapItem(QObject *parent)
    : State(parent),
      pixmapItem(nullptr)
{

}

bool StatePixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        if(pixmapItem == nullptr){
            pixmapItem = new PixmapItem(schScene,QPixmap("H:/eda/enginetest2/resources/123.png"));
            pixmapItem->setPos(mouseEvent->scenePos());

            schScene->addItem(pixmapItem);
        }
    }

    return true;
}

bool StatePixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    return true;
}

bool StatePixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    pixmapItem->createCommandAdd();
    pixmapItem = nullptr;
    return true;
}

bool StatePixmapItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    return true;
}

bool StatePixmapItem::keyPressEvent(QKeyEvent *keyEvent)
{
    return false;
}
