#include "pixmapitem.h"
#include "PartScene.h"

//#include "pixmapitemaddcommand.h"
//#include "pixmapitemremovecommand.h"
//#include "pixmapitemchangepropertycommand.h"
//#include "shapeitemmovecommand.h"

#include <QKeyEvent>

PixmapItem::PixmapItem(PartScene *scene, const QPixmap &pixmap, QGraphicsItem *parent)
    :QGraphicsPixmapItem(pixmap,parent),
      partScene(scene)
{
   setAcceptHoverEvents(true);
   setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable |QGraphicsItem::ItemIgnoresTransformations );

}

PixmapItem::~PixmapItem()
{
}

void PixmapItem::selected()
{
}

void PixmapItem::unselected()
{
}

int PixmapItem::type() const
{
    return Type;
}

//void PixmapItem::createCommandAdd()
//{
//    partScene->pushCommand(new PixmapItemAddCommand(this),true);
//}

//void PixmapItem::createCommandRemove()
//{
//    partScene->pushCommand(new PixmapItemRemoveCommand(this),true);

//}

//void PixmapItem::createCommandMove()
//{
//    partScene->pushCommand(new ShapeItemMoveCommand(this));

//}

void PixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(isMoved()){
//        createCommandMove();
    }
    QGraphicsPixmapItem::mouseReleaseEvent(mouseEvent);
}


void PixmapItem::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Space:
            setRotation(rotation() - 90);
            event->accept();
            break;
        default:
            break;
    }
}
