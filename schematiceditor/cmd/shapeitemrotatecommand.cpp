#include "shapeitemrotatecommand.h"

ShapeItemRotateCommand::ShapeItemRotateCommand(QGraphicsItem *item)
    :ItemUndoCommand(item),
      shapeItem(item)
{
    setText("ShapeItemRotateCommand");
    initialRotations = item->initialRotations;
    item->initialRotations.clear();

    for (auto i = initialRotations.cbegin(); i != initialRotations.cend(); ++i){
        i.key()->metadata["rotation"] = i.key()->rotation();
        newRotations.insert(i.key(),i.key()->rotation());
    }
}

void ShapeItemRotateCommand::undo()
{
    

    for (auto i = initialRotations.cbegin(); i != initialRotations.cend(); ++i){
        i.key()->setRotation(i.value());
        i.key()->metadata["rotation"] = i.value();
        if(i.key()->isSelected()){
            i.key()->setSelected(false);
        }
    }
}

void ShapeItemRotateCommand::redo()
{
    for (auto i = newRotations.cbegin(); i != newRotations.cend(); ++i){
        i.key()->setRotation(i.value());
        i.key()->metadata["rotation"] = i.value();
    }
}
