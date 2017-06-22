#ifndef PARTITEMMOVECOMMAND_H
#define PARTITEMMOVECOMMAND_H

#include "itemundocommand.h"
#include <QPointF>
#include <QHash>

class PartItem;

class PartItemMoveCommand : public ItemUndoCommand
{
public:
    PartItemMoveCommand(PartItem *item);

    void undo();
    void redo();
private:
    PartItem *partItem;

    QHash<QGraphicsItem *, QPointF> initialPositions;
    QPointF newPos;
};
#endif // PARTITEMMOVECOMMAND_H
