#include "textitemchangepropertycommand.h"
#include "textitem.h"

TextItemChangePropertyCommand::TextItemChangePropertyCommand(TextItem *item)
    :ItemUndoCommand(item),
      textItem(item)
{
    setText("TextItemChangePropertyCommand");
}

void TextItemChangePropertyCommand::undo()
{

}

void TextItemChangePropertyCommand::redo()
{

}
