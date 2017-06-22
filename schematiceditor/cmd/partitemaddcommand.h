#ifndef PARTITEMADDCOMMAND_H
#define PARTITEMADDCOMMAND_H

#include "itemundocommand.h"

class PartItem;

class PartItemAddCommand : public ItemUndoCommand
{
public:
    PartItemAddCommand(PartItem *item);
    ~PartItemAddCommand();

    void undo();
    void redo();
private:
    PartItem *partItem;
};

#endif // PARTITEMADDCOMMAND_H
