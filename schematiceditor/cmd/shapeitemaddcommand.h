#ifndef SHAPEITEMADDCOMMAND_H
#define SHAPEITEMADDCOMMAND_H

#include "itemundocommand.h"

class QGraphicsItem;

class ShapeItemAddCommand : public ItemUndoCommand
{
public:
    ShapeItemAddCommand(QGraphicsItem *item);
    ~ShapeItemAddCommand();

    void undo();
    void redo();
private:
    QGraphicsItem *shapeItem;
};

#endif // SHAPEITEMADDCOMMAND_H
