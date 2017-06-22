#include "textitemremovecommand.h"
#include "textitem.h"

TextItemRemoveCommand::TextItemRemoveCommand(TextItem *item)
    :ItemUndoCommand(item),
      textItem(item)
{
    setText("TextItemRemoveCommand");
}

void TextItemRemoveCommand::undo()
{

    schScene->addShape(textItem);


}

void TextItemRemoveCommand::redo()
{
    schScene->removeShape(textItem);


}
