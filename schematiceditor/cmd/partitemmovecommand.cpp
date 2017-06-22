#include "partitemmovecommand.h"
#include "partitem.h"

PartItemMoveCommand::PartItemMoveCommand(PartItem *item)
    :ItemUndoCommand(item),
      partItem(item)
{
    setText("PartItemMoveCommand");

    initialPositions = partItem->initialPositions;
    newPos = partItem->pos();
    for (auto i = initialPositions.constBegin(); i != initialPositions.constEnd(); ++i){
        i.key()->metadata["pos"] = i.key()->pos();
    }
}

void PartItemMoveCommand::undo()
{
    if(preUndoChildCount()){
        preUndo();qDebug() << "preUndo" ;
    }
    for (auto i = initialPositions.constBegin(); i != initialPositions.constEnd(); ++i){
        i.key()->setPos(i.value());
        i.key()->metadata["pos"] = i.value();
    }
     if(postUndoChildCount()){
         postUndo();qDebug() << "postUndo" ;
     }
}

void PartItemMoveCommand::redo()
{
    if(preRedoChildCount()){
        preRedo();qDebug() << "preRedo" ;
    }
    const QPointF delta = newPos - initialPositions.value(partItem);
    for (auto i = initialPositions.constBegin(); i != initialPositions.constEnd(); ++i){
        i.key()->setPos(i.value() + delta);
        i.key()->metadata["pos"] = i.value();
    }
    if(postRedoChildCount()){
        postRedo();qDebug() << "postRedo" ;
    }
}
