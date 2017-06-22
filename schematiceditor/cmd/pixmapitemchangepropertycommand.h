#ifndef PIXMAPITEMCHANGEPROPERTYCOMMAND_H
#define PIXMAPITEMCHANGEPROPERTYCOMMAND_H

#include "itemundocommand.h"

class PixmapItem;

class PixmapItemChangePropertyCommand : public ItemUndoCommand
{
public:
    PixmapItemChangePropertyCommand(PixmapItem *item);

    void undo();
    void redo();
private:
    PixmapItem *pixmapItem;
};

#endif // PIXMAPITEMCHANGEPROPERTYCOMMAND_H
