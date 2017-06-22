#include "partitemremovecommand.h"
#include "partitem.h"

PartItemRemoveCommand::PartItemRemoveCommand(PartItem *item)
    :ItemUndoCommand(item),
      partItem(item)
{
    setText("PartItemRemoveCommand");

}

PartItemRemoveCommand::~PartItemRemoveCommand()
{

}

void PartItemRemoveCommand::undo()
{

}

void PartItemRemoveCommand::redo()
{

}
