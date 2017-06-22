#ifndef TEXTITEMREMOVECOMMAND_H
#define TEXTITEMREMOVECOMMAND_H

#include "itemundocommand.h"

class TextItem;

class TextItemRemoveCommand : public ItemUndoCommand
{
public:
    TextItemRemoveCommand(TextItem *item);

    void undo();
    void redo();
private:
    TextItem *textItem;
};

#endif // TEXTITEMREMOVECOMMAND_H
