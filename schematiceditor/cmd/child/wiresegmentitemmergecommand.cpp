#include "wiresegmentitemmergecommand.h"
#include "wiresegmentitem.h"
#include "wire.h"
#include "portitem.h"
#include "junctionitem.h"

WireSegmentItemMergeCommand::WireSegmentItemMergeCommand(WireSegmentItem *item)
    :ItemUndoCommand(item),
      wireSegmentItem(item),
      preItem(item->preItem),
      nextItem(item->nextItem),
      attachedStartJunction(item->attachedStartJunction),
      attachedEndJunction(item->attachedEndJunction),
      attachedStartPort(item->attachedStartPort),
      attachedEndPort(item->attachedEndPort)
{
    //wireSegmentItem 为长度为0 要合并的线段
    redo();
}

WireSegmentItemMergeCommand::~WireSegmentItemMergeCommand()
{

}

void WireSegmentItemMergeCommand::undo()
{
    if(preItem){
        // wireSegmentItem 不可能为选中 nextItem在redo中自动失去选中状态
        preItem->setSelected(false);
        wireSegmentItem->attachedWire->nextInsert(preItem,wireSegmentItem);

        if(nextItem){
            preItem->nextItem = wireSegmentItem;
            if(nextItem->nextItem){
                nextItem->nextItem->preItem = nextItem;
            }
            QLineF tmpLine = preItem->line();
            tmpLine.setP2(preItem->mapFromItem(wireSegmentItem,wireSegmentItem->line().p1()));
            preItem->setLine(tmpLine);

            nextItem->setDeleted(false);
            wireSegmentItem->attachedWire->nextInsert(wireSegmentItem,nextItem);
        }else if(attachedEndJunction){
            attachedEndJunction->removePreWireSegmentItem(preItem);
            attachedEndJunction->addPreWireSegmentItem(wireSegmentItem);
            preItem->nextItem = wireSegmentItem;
        }else if(attachedEndPort){
            attachedEndPort->removePreWireSegmentItem(preItem);
            attachedEndPort->addPreWireSegmentItem(wireSegmentItem);
            preItem->nextItem = wireSegmentItem;
        }else{
            preItem->nextItem = wireSegmentItem;
        }
        wireSegmentItem->setDeleted(false);
    }else if(nextItem){
        // wireSegmentItem 不可能为选中
        nextItem->setSelected(false);
        wireSegmentItem->attachedWire->nextInsert(preItem,wireSegmentItem);

        if(attachedStartJunction){
            attachedStartJunction->removeNextWireSegmentItem(nextItem);
            attachedStartJunction->addNextWireSegmentItem(wireSegmentItem);
        }else if(attachedStartPort){
            attachedStartPort->removeNextWireSegmentItem(nextItem);
            attachedStartPort->addNextWireSegmentItem(wireSegmentItem);
        }else{
            nextItem->preItem = wireSegmentItem;
        }
        wireSegmentItem->setDeleted(false);
    }
}

void WireSegmentItemMergeCommand::redo()
{
    if (preItem) {
        wireSegmentItem->setDeleted(true);
        wireSegmentItem->attachedWire->removeOne(wireSegmentItem);

        if(nextItem){
            preItem->nextItem = nextItem->nextItem;
            if(nextItem->nextItem){
                nextItem->nextItem->preItem = preItem;
            }
            QLineF tmpLine = preItem->line();
            tmpLine.setP2(preItem->mapFromItem(nextItem,nextItem->line().p2()));

            // preItem和nextItem 移动都有可能导致 wireSegmentItem 长度为0
            // 元件移动也可以导致合并 但此时一般不为选中态
            bool selected = nextItem->isSelected() || preItem->isSelected();
            if(selected){
                preItem->setSelected(false);
            }
            preItem->setLine(tmpLine);
            if(selected){
                preItem->setSelected(true);
            }
            // 不可以通过场景删除或delete 否则无法处理鼠标释放事件
            nextItem->setDeleted(true);
            wireSegmentItem->attachedWire->removeOne(nextItem);

        }else if(attachedEndJunction){
            attachedEndJunction->removePreWireSegmentItem(wireSegmentItem);
            attachedEndJunction->addPreWireSegmentItem(preItem);
            preItem->nextItem = nullptr;
        }else if(attachedEndPort){
            attachedEndPort->removePreWireSegmentItem(wireSegmentItem);
            attachedEndPort->addPreWireSegmentItem(preItem);
            preItem->nextItem = nullptr;
        }else{
            preItem->nextItem = nullptr;
        }

    }else if(nextItem){
        wireSegmentItem->setDeleted(true);
        wireSegmentItem->attachedWire->removeOne(wireSegmentItem);

        if(attachedStartJunction){
            attachedStartJunction->removeNextWireSegmentItem(wireSegmentItem);
            attachedStartJunction->addNextWireSegmentItem(nextItem);
        }else if(wireSegmentItem->attachedStartPort){
            attachedStartPort->removeNextWireSegmentItem(wireSegmentItem);
            attachedStartPort->addNextWireSegmentItem(nextItem);
        }else{
            nextItem->preItem = nullptr;
        }
    }
}
