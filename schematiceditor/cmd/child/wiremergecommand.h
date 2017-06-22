#ifndef WIREMERGECOMMAND_H
#define WIREMERGECOMMAND_H

#include "itemundocommand.h"

class WireMergeCommand : public ItemUndoCommand
{
public:
    WireMergeCommand(WireSegmentItem *mergeFromItem);

    void undo();
    void redo();
private:
    WireSegmentItem *wireSegmentItem;
};

#endif // WIREMERGECOMMAND_H
