#ifndef WIRESEGMENTITEMMERGECOMMAND_H
#define WIRESEGMENTITEMMERGECOMMAND_H

#include "itemundocommand.h"

class WireSegmentItemMergeCommand : public ItemUndoCommand
{
public:
    WireSegmentItemMergeCommand(WireSegmentItem *item);
    ~WireSegmentItemMergeCommand();

    void undo();
    void redo();
private:
    WireSegmentItem *wireSegmentItem;
    WireSegmentItem *preItem;
    WireSegmentItem *nextItem;
    JunctionItem *attachedStartJunction;
    JunctionItem *attachedEndJunction;
    PortItem *attachedStartPort;
    PortItem *attachedEndPort;
};

#endif // WIRESEGMENTITEMMERGECOMMAND_H
