#ifndef WIRESEGMENTITEMPREPENDCOMMAND_H
#define WIRESEGMENTITEMPREPENDCOMMAND_H

#include "itemundocommand.h"

class WireSegmentItemPrependCommand : public ItemUndoCommand
{
public:
    WireSegmentItemPrependCommand(WireSegmentItem *item);

    void undo();
    void redo();
private:
    WireSegmentItem *wireSegmentItem;
    WireSegmentItem *newItem;
    PortItem *attachedStartPort;
};

#endif // WIRESEGMENTITEMPREPENDCOMMAND_H
