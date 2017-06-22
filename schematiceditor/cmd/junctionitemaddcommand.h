#ifndef JUNCTIONITEMADDCOMMAND_H
#define JUNCTIONITEMADDCOMMAND_H

#include "itemundocommand.h"

class JunctionItem;

class JunctionItemAddCommand : public ItemUndoCommand
{
public:
    JunctionItemAddCommand(JunctionItem *item);

    void undo();
    void redo();
};

#endif // JUNCTIONITEMADDCOMMAND_H
