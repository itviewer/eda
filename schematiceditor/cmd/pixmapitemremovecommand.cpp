#include "pixmapitemremovecommand.h"
#include "pixmapitem.h"

PixmapItemRemoveCommand::PixmapItemRemoveCommand(PixmapItem *item)
    :ItemUndoCommand(item),
      pixmapItem(item)
{
     setText("PixmapItemRemoveCommand");
}

void PixmapItemRemoveCommand::undo()
{

    schScene->addShape(pixmapItem);


}

void PixmapItemRemoveCommand::redo()
{
    schScene->removeShape(pixmapItem);


}
