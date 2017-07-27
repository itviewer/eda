#include "wiresegmentitemmovecommand.h"
#include "wiresegmentitem.h"

WireSegmentItemMoveCommand::WireSegmentItemMoveCommand(WireSegmentItem *item)
    :ItemUndoCommand(item),
      wireSegmentItem(item)
{

    setText("WireSegmentItemMoveCommand");

    initialPositions = wireSegmentItem->initialPositions;
    newPos = wireSegmentItem->pos();
    for (auto i = initialPositions.cbegin(); i != initialPositions.cend(); ++i){
        i.key()->metadata["pos"] = i.key()->pos();
    }
}

WireSegmentItemMoveCommand::~WireSegmentItemMoveCommand()
{

}

void WireSegmentItemMoveCommand::undo()
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

void WireSegmentItemMoveCommand::redo()
{
    if(preRedoChildCount()){
        preRedo();qDebug() << "preRedo" ;
    }
    const QPointF delta = newPos - initialPositions.value(wireSegmentItem);
    for (auto i = initialPositions.cbegin(); i != initialPositions.cend(); ++i){
        i.key()->setPos(i.value() + delta);
        i.key()->metadata["pos"] = i.value();
    }
    if(postRedoChildCount()){
        postRedo();qDebug() << "postRedo" ;
    }
}
