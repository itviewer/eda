#ifndef WIRESPILTCOMMAND_H
#define WIRESPILTCOMMAND_H

#include "itemundocommand.h"

class WireSpiltCommand : public ItemUndoCommand
{
public:
    WireSpiltCommand(WireSegmentItem *splitFromItem,JunctionItem *junction);

    void undo();
    void redo();
private:
    WireSegmentItem *wireSegmentItem;
    JunctionItem *attachedJunction;
    Wire *newWire;
};

#endif // WIRESPILTCOMMAND_H
