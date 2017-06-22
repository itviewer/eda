#ifndef WIRESEGMENTITEMCHANGEGEOMETRYCOMMAND_H
#define WIRESEGMENTITEMCHANGEGEOMETRYCOMMAND_H

#include "itemundocommand.h"

class WireSegmentItem;

class WireSegmentItemChangeGeometryCommand : public ItemUndoCommand
{
public:
    WireSegmentItemChangeGeometryCommand(WireSegmentItem *item);
    void undo();
    void redo();
private:
    WireSegmentItem *wireSegmentItem;
};


#endif // WIRESEGMENTITEMCHANGEGEOMETRYCOMMAND_H
