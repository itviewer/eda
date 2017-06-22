#ifndef SHAPEITEMMOVECOMMAND_H
#define SHAPEITEMMOVECOMMAND_H

#include "itemundocommand.h"
#include <QPointF>
#include <QHash>

class QGraphicsItem;

class ShapeItemMoveCommand : public ItemUndoCommand
{
public:
    ShapeItemMoveCommand(QGraphicsItem *item);

    void undo();
    void redo();
private:
    QGraphicsItem *shapeItem;

    QHash<QGraphicsItem *, QPointF> initialPositions;
    QPointF newPos;
};
#endif // SHAPEITEMMOVECOMMAND_H
