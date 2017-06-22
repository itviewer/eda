#ifndef TEXTITEMCHANGEPROPERTYCOMMAND_H
#define TEXTITEMCHANGEPROPERTYCOMMAND_H

#include "itemundocommand.h"

class TextItem;

class TextItemChangePropertyCommand : public ItemUndoCommand
{
public:
    TextItemChangePropertyCommand(TextItem *item);
    void undo();
    void redo();
private:
    TextItem *textItem;
};

#endif // TEXTITEMCHANGEPROPERTYCOMMAND_H
