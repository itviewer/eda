#include "partitemaddcommand.h"
#include "partitem.h"

PartItemAddCommand::PartItemAddCommand(PartItem *item)
    :ItemUndoCommand(item),
      partItem(item)
{
    setText("PartItemAddCommand");

    partItem->metadata["pos"] = partItem->pos();
}

PartItemAddCommand::~PartItemAddCommand()
{

}

void PartItemAddCommand::undo()
{
    partItem->hide();
    schScene->removePart(partItem);
}

void PartItemAddCommand::redo()
{
    partItem->show();
    schScene->addPart(partItem);
}
