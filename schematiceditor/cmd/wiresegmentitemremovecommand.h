#ifndef WIRESEGMENTITEMREMOVECOMMAND_H
#define WIRESEGMENTITEMREMOVECOMMAND_H

#include "itemundocommand.h"

class WireSegmentItem;

class WireSegmentItemRemoveCommand : public ItemUndoCommand
{
public:
    WireSegmentItemRemoveCommand(WireSegmentItem *item);
    void undo();
    void redo();
private:
    WireSegmentItem *wireSegmentItem;
};

#endif // WIRESEGMENTITEMREMOVECOMMAND_H
