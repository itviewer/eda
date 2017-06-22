#ifndef PARTITEMREMOVECOMMAND_H
#define PARTITEMREMOVECOMMAND_H

#include "itemundocommand.h"

class PartItem;

class PartItemRemoveCommand : public ItemUndoCommand
{
public:
    PartItemRemoveCommand(PartItem *item);
    ~PartItemRemoveCommand();

    void undo();
    void redo();
private:
    PartItem *partItem;
};

#endif // PARTITEMREMOVECOMMAND_H
