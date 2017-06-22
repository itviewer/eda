#include "itemundocommand.h"

ItemUndoCommand::ItemUndoCommand(QGraphicsItem *item)
    :QUndoCommand(nullptr),
      item(item)
{
    schScene = static_cast<SchematicScene *>(item->scene());
}

// 若命令被销毁 无论子类是否自定义析构函数 父类的析构函数一定被调用
ItemUndoCommand::~ItemUndoCommand()
{
}

int ItemUndoCommand::type() const
{
    return Type;
}

void ItemUndoCommand::undo()
{
    schScene->clearSelection();
}

void ItemUndoCommand::redo()
{
}
