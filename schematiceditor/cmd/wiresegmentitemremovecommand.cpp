#include "wiresegmentitemremovecommand.h"
#include "wiresegmentitem.h"

WireSegmentItemRemoveCommand::WireSegmentItemRemoveCommand(WireSegmentItem *item)
    :ItemUndoCommand(item),
      wireSegmentItem(item)
{
    setText("WireSegmentItemRemoveCommand");
}

void WireSegmentItemRemoveCommand::undo()
{

}

void WireSegmentItemRemoveCommand::redo()
{

}
