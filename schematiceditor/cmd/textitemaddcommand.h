#ifndef TEXTITEMADDCOMMAND_H
#define TEXTITEMADDCOMMAND_H

#include "itemundocommand.h"

class TextItem;

class TextItemAddCommand : public ItemUndoCommand
{
public:
    TextItemAddCommand(TextItem *item);
    ~TextItemAddCommand();

    void undo();
    void redo();
private:
    TextItem *textItem;
};

#endif // TEXTITEMADDCOMMAND_H
