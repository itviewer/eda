#include "shapeitemmovecommand.h"

ShapeItemMoveCommand::ShapeItemMoveCommand(QGraphicsItem *item)
    :ItemUndoCommand(item),
      shapeItem(item)
{
    setText("ShapeItemMoveCommand");

    initialPositions = shapeItem->initialPositions;
    newPos = shapeItem->pos();
    for (auto i = initialPositions.cbegin(); i != initialPositions.cend(); ++i){
        i.key()->metadata["pos"] = i.key()->pos();
    }
}

void ShapeItemMoveCommand::undo()
{

    if(preUndoChildCount()){
        preUndo();qDebug() << "preUndo" ;
    }
    for (auto i = initialPositions.cbegin(); i != initialPositions.cend(); ++i){
        i.key()->setPos(i.value());
        i.key()->metadata["pos"] = i.value();
    }
    if(postUndoChildCount()){
        postUndo();qDebug() << "postUndo" ;
    }
}

void ShapeItemMoveCommand::redo()
{
    if(preRedoChildCount()){
        preRedo();qDebug() << "preRedo" ;
    }
    const QPointF delta = newPos - initialPositions.value(shapeItem);
    for (auto i = initialPositions.cbegin(); i != initialPositions.cend(); ++i){
        i.key()->setPos(i.value() + delta);
        i.key()->metadata["pos"] = i.value();
    }
    if(postRedoChildCount()){
        postRedo();qDebug() << "postRedo" ;
    }
}
