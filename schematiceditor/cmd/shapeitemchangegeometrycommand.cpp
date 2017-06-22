#include "shapeitemchanggeometryecommand.h"

ShapeItemChangeGeometryCommand::ShapeItemChangeGeometryCommand(QGraphicsItem *item)
    :ItemUndoCommand(item),
      shapeItem(item)
{
    setText("ShapeItemChangeGeometryCommand");
    originGeometry = shapeItem->originGeometry;
    newGeometry = shapeItem->metadata["geometry"];
    shapeItem->setTransformOriginPoint(shapeItem->boundingRect().center());
}

void ShapeItemChangeGeometryCommand::undo()
{


    shapeItem->setGeometry(originGeometry);
    shapeItem->metadata["geometry"] = originGeometry;
    shapeItem->setTransformOriginPoint(shapeItem->boundingRect().center());
}

void ShapeItemChangeGeometryCommand::redo()
{
    shapeItem->setGeometry(newGeometry);
    shapeItem->metadata["geometry"] = newGeometry;
    shapeItem->setTransformOriginPoint(shapeItem->boundingRect().center());
}
