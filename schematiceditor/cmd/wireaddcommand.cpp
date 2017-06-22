#include "wireaddcommand.h"
#include "wiresegmentitem.h"

#include "junctionitem.h"
#include "portitem.h"

WireAddCommand::WireAddCommand(Wire *wire)
    :WireUndoCommand(wire)
{
    setText("WireAddCommand");

    attachedStartJunction = wire->attachedStartJunction();
    attachedEndJunction = wire->attachedEndJunction();

    attachedStartPort = wire->attachedStartPort();
    attachedEndPort = wire->attachedEndPort();


    // 设置网络名
    originEndNetName = attachedEndJunction ? attachedEndJunction->attachedNet() : "";

    if(attachedStartJunction){
        netName = attachedStartJunction->attachedNet();
    }else if(attachedEndJunction){
        netName = originEndNetName;
    }else{
        netName = makeNetName();
    }
    wire->setAttachedNet(netName);

    // 终点为连结点且起点连接到网络
    if(attachedEndJunction && attachedStartJunction){
        attachedEndJunction->setAttachedNet(netName);

        for(WireSegmentItem *item:attachedEndJunction->attachedNextWireSegmentItems){
            item->attachedWire->setAttachedNet(netName);
        }
        for(WireSegmentItem *item:attachedEndJunction->attachedPreWireSegmentItems){
            item->attachedWire->setAttachedNet(netName);
        }
     }
}

WireAddCommand::~WireAddCommand()
{
    //TODO 被销毁彻底删除导线段
}

void WireAddCommand::undo()
{
    if(preUndoChildCount()){
        preUndo();qDebug() << "preUndo" ;
    }

    for(WireSegmentItem *item:wire->wireItems){
        item->setDeleted(true);
    }
    // 起点分别连接到端口、导线、连结点的处理 顺序不可更改
    if(attachedStartPort){
        attachedStartPort->removeNextWireSegmentItem(wire->firstItem());
    }else if(attachedStartJunction){
        attachedStartJunction->removeNextWireSegmentItem(wire->firstItem());
    }

    // 终点分别连接到端口、导线、连结点的处理 顺序不可更改
    if(attachedEndPort){
        attachedEndPort->removePreWireSegmentItem(wire->lastItem());
    }else if(attachedEndJunction){
        attachedEndJunction->removePreWireSegmentItem(wire->lastItem());
        // 终点为连结点且起点连接到网络
        if(attachedStartJunction){
            attachedEndJunction->setAttachedNet(originEndNetName);

            for(WireSegmentItem *item:attachedEndJunction->attachedNextWireSegmentItems){
                item->attachedWire->setAttachedNet(originEndNetName);
            }
            for(WireSegmentItem *item:attachedEndJunction->attachedPreWireSegmentItems){
                item->attachedWire->setAttachedNet(originEndNetName);
            }
        }
    }

    if(postUndoChildCount()){
        postUndo();qDebug() << "postUndo" ;
    }
}

void WireAddCommand::redo()
{
    if(preRedoChildCount()){
        preRedo();qDebug() << "preRedo" ;
    }

    for(WireSegmentItem *item:wire->wireItems){
        item->setDeleted(false);
    }
    if(attachedStartPort){
        attachedStartPort->addNextWireSegmentItem(wire->firstItem());
    }else if(attachedStartJunction){
        attachedStartJunction->addNextWireSegmentItem(wire->firstItem());
    }

    if(attachedEndPort){
        attachedEndPort->addPreWireSegmentItem(wire->lastItem());
    }else if(attachedEndJunction){
        // 终点为连结点且起点连接到网络
        if(attachedStartJunction){
            attachedEndJunction->setAttachedNet(netName);

            for(WireSegmentItem *item:attachedEndJunction->attachedNextWireSegmentItems){
                item->attachedWire->setAttachedNet(netName);
            }
            for(WireSegmentItem *item:attachedEndJunction->attachedPreWireSegmentItems){
                item->attachedWire->setAttachedNet(netName);
            }
        }

        attachedEndJunction->addPreWireSegmentItem(wire->lastItem());
    }

    if(postRedoChildCount()){
        postRedo();qDebug() << "postRedo" ;
    }
}
