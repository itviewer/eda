#include "pixmapitemaddcommand.h"
#include "pixmapitem.h"

PixmapItemAddCommand::PixmapItemAddCommand(PixmapItem *item)
    :ItemUndoCommand(item),
      pixmapItem(item)
{
    setText("PixmapItemAddCommand");
    pixmapItem->metadata["pos"] = pixmapItem->pos();
    pixmapItem->setTransformOriginPoint(pixmapItem->boundingRect().center());
}

PixmapItemAddCommand::~PixmapItemAddCommand()
{
}

void PixmapItemAddCommand::undo()
{

    schScene->removeShape(pixmapItem);


}

void PixmapItemAddCommand::redo()
{

    schScene->addShape(pixmapItem);


}
