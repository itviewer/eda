#include "wireundocommand.h"

WireUndoCommand::WireUndoCommand(Wire *wire)
    :QUndoCommand(nullptr),
      wire(wire)
{
    schScene = wire->schScene;
}

int WireUndoCommand::type() const
{
    return Type;
}

void WireUndoCommand::undo()
{

}

void WireUndoCommand::redo()
{

}
