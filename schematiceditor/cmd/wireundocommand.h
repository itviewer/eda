#ifndef WIREUNDOCOMMAND_H
#define WIREUNDOCOMMAND_H

#include <QUndoCommand>
#include "schematicscene.h"
#include "wire.h"

class WireUndoCommand : public QUndoCommand
{
public:
    WireUndoCommand(Wire *wire);

    enum {
        Type = Command::WireUndoCommandType
    };

    Wire *wire;
    SchematicScene *schScene;

    int type() const;

    void undo();
    void redo();
};

#endif // WIREUNDOCOMMAND_H
