#include "pixmapitemchangepropertycommand.h"
#include "pixmapitem.h"

PixmapItemChangePropertyCommand::PixmapItemChangePropertyCommand(PixmapItem *item)
    :ItemUndoCommand(item),
      pixmapItem(item)
{

    setText("PixmapItemChangePropertyCommand");
}

void PixmapItemChangePropertyCommand::undo()
{

}

void PixmapItemChangePropertyCommand::redo()
{

}
