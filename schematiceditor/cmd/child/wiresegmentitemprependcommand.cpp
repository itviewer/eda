#include "wiresegmentitemprependcommand.h"
#include "wiresegmentitem.h"
#include "wire.h"
#include "portitem.h"

WireSegmentItemPrependCommand::WireSegmentItemPrependCommand(WireSegmentItem *item)
    :ItemUndoCommand(item),
      wireSegmentItem(item),
      attachedStartPort(item->attachedStartPort),
      newItem(nullptr)
{
    redo();
}

void WireSegmentItemPrependCommand::undo()
{
    schScene->removeItem(newItem);

    attachedStartPort->removeNextWireSegmentItem(newItem);
    attachedStartPort->addNextWireSegmentItem(wireSegmentItem);

    wireSegmentItem->preItem = nullptr;

    wireSegmentItem->attachedWire->removeFirst();
}

void WireSegmentItemPrependCommand::redo()
{
    if(!newItem){
        newItem = new WireSegmentItem(schScene);
        newItem->isHorizontalMode = !wireSegmentItem->isHorizontalMode;
        newItem->setPen(wireSegmentItem->normalPen);
        newItem->setPos(wireSegmentItem->attachedStartPort->scenePos());

        QLineF tmpLine;
        tmpLine.setP2(newItem->mapFromItem(wireSegmentItem,wireSegmentItem->line().p1()));
        newItem->setLine(tmpLine);
    }

    schScene->addItem(newItem);

    attachedStartPort->removeNextWireSegmentItem(wireSegmentItem);
    attachedStartPort->addNextWireSegmentItem(newItem);

    wireSegmentItem->preItem = newItem;
    newItem->nextItem = wireSegmentItem;

    wireSegmentItem->attachedWire->prepend(newItem);
}
