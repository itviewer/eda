#include "wirespiltcommand.h"
#include "wiresegmentitem.h"
#include "wire.h"
#include "junctionitem.h"


WireSpiltCommand::WireSpiltCommand(WireSegmentItem *splitFromItem, JunctionItem *junction)
    :ItemUndoCommand(splitFromItem),
      wireSegmentItem(splitFromItem),
      attachedJunction(junction)
{
    redo();
}

void WireSpiltCommand::undo()
{
    wireSegmentItem->attachedWire->merge(newWire);
    attachedJunction->setDeleted(true);
}

void WireSpiltCommand::redo()
{
    attachedJunction->setDeleted(false);
    newWire = wireSegmentItem->attachedWire->junctionSplit(wireSegmentItem,attachedJunction);
}
