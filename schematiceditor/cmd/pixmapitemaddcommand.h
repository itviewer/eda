#ifndef PIXMAPITEMADDCOMMAND_H
#define PIXMAPITEMADDCOMMAND_H

#include "itemundocommand.h"

class PixmapItem;

class PixmapItemAddCommand : public ItemUndoCommand
{
public:
    PixmapItemAddCommand(PixmapItem *item);
    ~PixmapItemAddCommand();

    void undo();
    void redo();
private:
    PixmapItem *pixmapItem;
};


#endif // PIXMAPITEMADDCOMMAND_H
