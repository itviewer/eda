#include "wiresegmentitemappendcommand.h"
#include "wiresegmentitem.h"
#include "wire.h"
#include "portitem.h"

WireSegmentItemAppendCommand::WireSegmentItemAppendCommand(WireSegmentItem *item)
    :ItemUndoCommand(item),
      wireSegmentItem(item),
      attachedEndPort(item->attachedEndPort),
      newItem(nullptr)
{
    redo();
}

void WireSegmentItemAppendCommand::undo()
{
    schScene->removeItem(newItem);

    attachedEndPort->removePreWireSegmentItem(newItem);
    attachedEndPort->addPreWireSegmentItem(wireSegmentItem);

    wireSegmentItem->nextItem = nullptr;

    wireSegmentItem->attachedWire->removeLast();
}

void WireSegmentItemAppendCommand::redo()
{
    if(!newItem){
        newItem = new WireSegmentItem(schScene);

        newItem->isHorizontalMode = !wireSegmentItem->isHorizontalMode;
        newItem->setPen(wireSegmentItem->normalPen);
        newItem->setPos(wireSegmentItem->attachedEndPort->scenePos());

        QLineF tmpLine;
        tmpLine.setP1(newItem->mapFromItem(wireSegmentItem,wireSegmentItem->line().p2()));
        newItem->setLine(tmpLine);
    }

    schScene->addItem(newItem);

    attachedEndPort->removePreWireSegmentItem(wireSegmentItem);
    attachedEndPort->addPreWireSegmentItem(newItem);

    wireSegmentItem->nextItem = newItem;
    newItem->preItem = wireSegmentItem;

    wireSegmentItem->attachedWire->append(newItem);
}
