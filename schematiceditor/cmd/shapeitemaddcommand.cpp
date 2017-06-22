#include "shapeitemaddcommand.h"

ShapeItemAddCommand::ShapeItemAddCommand(QGraphicsItem *item)
    :ItemUndoCommand(item),
      shapeItem(item)
{
    setText("ShapeItemAddCommand");
    shapeItem->metadata["pos"] = shapeItem->pos();
    shapeItem->setTransformOriginPoint(shapeItem->boundingRect().center());
}

ShapeItemAddCommand::~ShapeItemAddCommand()
{
}

void ShapeItemAddCommand::undo()
{


    schScene->removeShape(shapeItem);
}

void ShapeItemAddCommand::redo()
{
    schScene->addShape(shapeItem);


}
