#include "pixmapitem.h"
#include "schematicscene.h"

#include "pixmapitemaddcommand.h"
#include "pixmapitemremovecommand.h"
#include "pixmapitemchangepropertycommand.h"
#include "shapeitemmovecommand.h"

#include <QKeyEvent>

PixmapItem::PixmapItem(SchematicScene *scene, const QPixmap &pixmap, QGraphicsItem *parent)
    :QGraphicsPixmapItem(pixmap,parent),
      schScene(scene)
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

void PixmapItem::createCommandAdd()
{
    schScene->pushCommand(new PixmapItemAddCommand(this),true);
}

void PixmapItem::createCommandRemove()
{
    schScene->pushCommand(new PixmapItemRemoveCommand(this),true);

}

void PixmapItem::createCommandMove()
{
    schScene->pushCommand(new ShapeItemMoveCommand(this));

}

void PixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(isMoved()){
        createCommandMove();
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
