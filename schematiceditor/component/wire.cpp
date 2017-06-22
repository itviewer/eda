#include "wire.h"
#include "wiresegmentitem.h"
#include "schematicscene.h"
#include "junctionitem.h"

#include "wireaddcommand.h"

Wire::Wire(SchematicScene *scene)
    :schScene(scene),
      netName("")
{

}

WireSegmentItem *Wire::firstItem() const
{
    return wireItems.first();
}

WireSegmentItem *Wire::lastItem() const
{
    return wireItems.last();
}

void Wire::createCommandAdd()
{
    schScene->pushCommand(new WireAddCommand(this));
}

void Wire::setAttachedNet(const QString &net)
{
    netName = net;
}

const QString Wire::attachedNet()
{
    return netName;
}

int Wire::count() const
{
    return wireItems.count();
}

bool Wire::isEmpty() const
{
    return wireItems.isEmpty();
}

void Wire::append(WireSegmentItem *wireSegmentItem)
{
    wireSegmentItem->attachedWire = this;
    wireItems.append(wireSegmentItem);
}

void Wire::prepend(WireSegmentItem *wireSegmentItem)
{
    wireSegmentItem->attachedWire = this;
    wireItems.prepend(wireSegmentItem);
}

void Wire::preInsert(WireSegmentItem *wireSegmentItem, WireSegmentItem *newItem)
{
    wireItems.insert(qMax(wireItems.indexOf(wireSegmentItem),0),newItem);
}

void Wire::nextInsert(WireSegmentItem *wireSegmentItem,WireSegmentItem *newItem)
{
    wireItems.insert(wireItems.indexOf(wireSegmentItem) + 1,newItem);
}

void Wire::removeFirst()
{
    wireItems.removeFirst();
}

void Wire::removeLast()
{
    wireItems.removeLast();
}

bool Wire::removeOne(WireSegmentItem *wireSegmentItem)
{
    return wireItems.removeOne(wireSegmentItem);
}

JunctionItem *Wire::attachedStartJunction() const
{
    return wireItems.first()->attachedStartJunction;
}

JunctionItem *Wire::attachedEndJunction() const
{
    return wireItems.last()->attachedEndJunction;
}

PortItem *Wire::attachedStartPort() const
{
    return wireItems.first()->attachedStartPort;
}

PortItem *Wire::attachedEndPort() const
{
    return wireItems.last()->attachedEndPort;
}


Wire * Wire::removeSplit(WireSegmentItem *wireSegmentItem)
{
    const int index = wireItems.indexOf(wireSegmentItem);
    delete wireSegmentItem;

    wireItems.at(index - 1)->nextItem = nullptr;
    wireItems.at(index + 1)->preItem = nullptr;

    Wire *splitWire = new Wire(schScene);
    splitWire->setAttachedNet(makeNetName());
    splitWire->wireItems = wireItems.mid(index + 1);

    for(WireSegmentItem *item:splitWire->wireItems){
        item->attachedWire = splitWire;
    }

    // 移除新wire的线段
    QList<WireSegmentItem *>::iterator start;
    start = wireItems.begin() + index;
    wireItems.erase(start,wireItems.end());

    return splitWire;
}

Wire * Wire::junctionSplit(WireSegmentItem *wireSegmentItem, JunctionItem *junction)
{
    const int index = wireItems.indexOf(wireSegmentItem);
    Wire *splitWire = new Wire(schScene);
    splitWire->setAttachedNet(netName);
    const QPointF junctionPos = junction->pos();
    if(wireSegmentItem->endPoint() == junctionPos){
        junction->addNextWireSegmentItem(wireSegmentItem->nextItem);
        junction->addPreWireSegmentItem(wireSegmentItem);
        wireSegmentItem->nextItem->preItem = nullptr;
        wireSegmentItem->nextItem = nullptr;

        splitWire->wireItems = wireItems.mid(index + 1);
    }else{
        // 自动将wireSegmentItem的nextItem置空
        WireSegmentItem *newWireSegmentItem = wireSegmentItem->junctionSplit(junctionPos);

        junction->addNextWireSegmentItem(newWireSegmentItem);
        junction->addPreWireSegmentItem(wireSegmentItem);

        splitWire->wireItems = wireItems.mid(index + 1);
        splitWire->prepend(newWireSegmentItem);
    }
    for(WireSegmentItem *item:splitWire->wireItems){
        item->attachedWire = splitWire;
    }
    // 移除旧wire中包含的新wire线段
    QList<WireSegmentItem *>::iterator start;
    start = wireItems.begin() + index + 1;
    wireItems.erase(start,wireItems.end());
    return splitWire;
}

void Wire::merge(Wire *wire)
{
    WireSegmentItem *mergeStartItem = lastItem();
    WireSegmentItem *mergeEndItem = wire->firstItem();
    if(mergeStartItem->attachedEndJunction){
        mergeStartItem->attachedEndJunction->removePreWireSegmentItem(mergeStartItem);
    }
    if(mergeEndItem->attachedStartJunction){
        mergeEndItem->attachedStartJunction->removeNextWireSegmentItem(mergeEndItem);
    }
//    qDebug() << mergeStartItem->isHorizontalMode << mergeEndItem->isHorizontalMode ;
    if(mergeStartItem->isHorizontalMode == mergeEndItem->isHorizontalMode){
        QLineF tmpLine = mergeStartItem->line();
        tmpLine.setP2(mergeStartItem->mapFromItem(mergeEndItem,mergeEndItem->line().p2()));
        mergeStartItem->setLine(tmpLine);

        wire->removeFirst();
        // TODO 需要先于nextItem->preItem = mergeStartItem 执行 不知为什么
        schScene->removeItem(mergeEndItem);
        delete mergeEndItem;

        WireSegmentItem *nextItem = wire->firstItem();
        if(nextItem){
            nextItem->preItem = mergeStartItem;
            mergeStartItem->nextItem = nextItem;
        }

        for(WireSegmentItem *item:wire->wireItems){
            item->attachedWire = this;
        }

        wireItems += wire->wireItems;
        delete wire;
    }else{
        mergeStartItem->nextItem = mergeEndItem;
        mergeEndItem->preItem = mergeStartItem;

        for(WireSegmentItem *item:wire->wireItems){
            item->attachedWire = this;
        }
        wireItems += wire->wireItems;

        delete wire;
    }
}

