#include "textitemaddcommand.h"
#include "textitem.h"

TextItemAddCommand::TextItemAddCommand(TextItem *item)
    :ItemUndoCommand(item),
      textItem(item)
{
    setText("TextItemAddCommand");
    textItem->metadata["pos"] = textItem->pos();
    textItem->metadata["text"] = textItem->text();
}

TextItemAddCommand::~TextItemAddCommand()
{
}

void TextItemAddCommand::undo()
{
    schScene->removeShape(textItem);


}

void TextItemAddCommand::redo()
{
    schScene->addShape(textItem);

}
