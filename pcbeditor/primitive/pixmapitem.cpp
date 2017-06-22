#include "pixmapitem.h"
#include "pcbscene.h"

//#include "pixmapitemaddcommand.h"
//#include "pixmapitemremovecommand.h"
//#include "pixmapitemchangepropertycommand.h"
//#include "shapeitemmovecommand.h"

#include <QKeyEvent>

PixmapItem::PixmapItem(PCBScene *scene, const QPixmap &pixmap, QGraphicsItem *parent)
    :QGraphicsPixmapItem(pixmap,parent),
      pcbScene(scene)
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
//    pcbScene->pushCommand(new PixmapItemAddCommand(this),true);
//}

//void PixmapItem::createCommandRemove()
//{
//    pcbScene->pushCommand(new PixmapItemRemoveCommand(this),true);

//}

//void PixmapItem::createCommandMove()
//{
//    pcbScene->pushCommand(new ShapeItemMoveCommand(this));

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
