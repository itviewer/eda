#include "parteditorrpc.h"
//#include "global.h"
//#include "parteditor.h"

PartEditorRPC::PartEditorRPC(QRemoteObjectNode *node,QObject *parent)
    :PartEditorRPCSource(parent),
      rpcNode(node)
{
//    connect(this,&PartEditorRPC::test, ptr->data(),&ControlCenterRPCReplica::justtest);

    ptr.reset(rpcNode->acquire<ControlCenterRPCReplica>());

    connect(ptr.data(),&ControlCenterRPCReplica::initialized,this,&PartEditorRPC::xxoo);

    connect(ptr.data(),&ControlCenterRPCReplica::stateChanged,this,[=](QRemoteObjectReplica::State state,QRemoteObjectReplica::State oldState){
        qDebug() << state << oldState << ptr.data()->isReplicaValid();
    });
}

void PartEditorRPC::xxoo()
{
    qDebug() << 111 ;
//    QMetaObject::invokeMethod(ptr.data(),"justtest");
}
