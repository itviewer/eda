#ifndef WIRESEGMENTITEMMOVECOMMAND_H
#define WIRESEGMENTITEMMOVECOMMAND_H

#include "itemundocommand.h"

class WireSegmentItem;

class WireSegmentItemMoveCommand : public ItemUndoCommand
{
public:
    WireSegmentItemMoveCommand(WireSegmentItem *item);
    ~WireSegmentItemMoveCommand();

    void undo();
    void redo();
private:
    WireSegmentItem *wireSegmentItem;

    QHash<QGraphicsItem *, QPointF> initialPositions;
    QPointF newPos;
};
#endif // WIRESEGMENTITEMMOVECOMMAND_H
