#include "shapeitemremovecommand.h"

ShapeItemRemoveCommand::ShapeItemRemoveCommand(QGraphicsItem *item)
    :ItemUndoCommand(item),
      shapeItem(item)
{
    setText("ShapeItemRemoveCommand");
}

void ShapeItemRemoveCommand::undo()
{


    schScene->addShape(shapeItem);
}

void ShapeItemRemoveCommand::redo()
{
    schScene->removeShape(shapeItem);


}
