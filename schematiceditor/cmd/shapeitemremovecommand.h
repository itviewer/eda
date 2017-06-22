#ifndef SHAPEITEMREMOVECOMMAND_H
#define SHAPEITEMREMOVECOMMAND_H

#include "itemundocommand.h"

class QGraphicsItem;

class ShapeItemRemoveCommand : public ItemUndoCommand
{
public:
    ShapeItemRemoveCommand(QGraphicsItem *item);

    void undo();
    void redo();
private:
    QGraphicsItem *shapeItem;
};

#endif // SHAPEITEMREMOVECOMMAND_H
