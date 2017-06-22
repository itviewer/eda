#include "shapeitemgrouprotatecommand.h"

ShapeItemGroupRotateCommand::ShapeItemGroupRotateCommand(QGraphicsItem *item)
    :ItemUndoCommand(item),
      shapeItem(item)
{

}

void ShapeItemGroupRotateCommand::undo()
{

}

void ShapeItemGroupRotateCommand::redo()
{

}
