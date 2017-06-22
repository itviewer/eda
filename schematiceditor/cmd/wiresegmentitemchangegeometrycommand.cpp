#include "wiresegmentitemchangegeometrycommand.h"
#include "wiresegmentitem.h"

WireSegmentItemChangeGeometryCommand::WireSegmentItemChangeGeometryCommand(WireSegmentItem *item)
    :ItemUndoCommand(item),
      wireSegmentItem(item)
{
    setText("WireSegmentItemChangeGeometryCommand");

}

void WireSegmentItemChangeGeometryCommand::undo()
{

}

void WireSegmentItemChangeGeometryCommand::redo()
{

}
