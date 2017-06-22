#ifndef SHAPEITEMROTATECOMMAND_H
#define SHAPEITEMROTATECOMMAND_H

#include "itemundocommand.h"
#include <QHash>

class QGraphicsItem;

class ShapeItemRotateCommand : public ItemUndoCommand
{
public:
    ShapeItemRotateCommand(QGraphicsItem *item);

    void undo();
    void redo();
private:
    QGraphicsItem *shapeItem;
    QHash<QGraphicsItem *, qreal> initialRotations;
    QHash<QGraphicsItem *, qreal> newRotations;
};

#endif // SHAPEITEMROTATECOMMAND_H
