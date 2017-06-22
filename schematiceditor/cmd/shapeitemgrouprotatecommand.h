#ifndef SHAPEITEMGROUPROTATECOMMAND_H
#define SHAPEITEMGROUPROTATECOMMAND_H

#include "itemundocommand.h"
class QGraphicsItem;

class ShapeItemGroupRotateCommand : public ItemUndoCommand
{
public:
    ShapeItemGroupRotateCommand(QGraphicsItem *item);

    void undo();
    void redo();
private:
    QGraphicsItem *shapeItem;

    qreal newRotation;
};

#endif // SHAPEITEMGROUPROTATECOMMAND_H
