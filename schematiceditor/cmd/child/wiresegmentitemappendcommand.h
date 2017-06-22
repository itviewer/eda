#ifndef WIRESEGMENTITEMAPPENDCOMMAND_H
#define WIRESEGMENTITEMAPPENDCOMMAND_H

#include "itemundocommand.h"

class WireSegmentItemAppendCommand : public ItemUndoCommand
{
public:
    WireSegmentItemAppendCommand(WireSegmentItem *item);

    void undo();
    void redo();
private:
    WireSegmentItem *wireSegmentItem;
    WireSegmentItem *newItem;
    PortItem *attachedEndPort;
};


#endif // WIRESEGMENTITEMAPPENDCOMMAND_H
