#ifndef UNDOCOMMAND_H
#define UNDOCOMMAND_H

#include <QUndoCommand>
#include "schematicscene.h"
#include <QGraphicsItem>

class QGraphicsItem;
class SchematicScene;

class ItemUndoCommand : public QUndoCommand
{
public:
    ItemUndoCommand(QGraphicsItem *item);
    ~ItemUndoCommand();

    enum {
        Type = Command::ItemUndoCommandType
    };

    QGraphicsItem *item;
    SchematicScene *schScene;

    int type() const;

    void undo();
    void redo();
};

#endif // UNDOCOMMAND_H
