#include "wiremergecommand.h"
#include "wiresegmentitem.h"

WireMergeCommand::WireMergeCommand(WireSegmentItem *mergeFromItem)
    :ItemUndoCommand(mergeFromItem)
{

}

void WireMergeCommand::undo()
{

}

void WireMergeCommand::redo()
{

}
