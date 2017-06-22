#ifndef PIXMAPITEMREMOVECOMMAND_H
#define PIXMAPITEMREMOVECOMMAND_H

#include "itemundocommand.h"

class PixmapItem;

class PixmapItemRemoveCommand : public ItemUndoCommand
{
public:
    PixmapItemRemoveCommand(PixmapItem *item);

    void undo();
    void redo();
private:
    PixmapItem *pixmapItem;
};

#endif // PIXMAPITEMREMOVECOMMAND_H
