#include "controlcenterrpc.h"

ControlCenterRPC::ControlCenterRPC(QRemoteObjectNode *node, QObject *parent)
    :ControlCenterRPCSource(parent),
      registryNode(node)
{
    connect(registryNode->registry(),&QRemoteObjectRegistry::remoteObjectAdded,this,[this](const QRemoteObjectSourceLocation &entry){
            qDebug() <<  registryNode->registry()->sourceLocations();
    });

    connect(registryNode->registry(),&QRemoteObjectRegistry::remoteObjectRemoved,this,[this](const QRemoteObjectSourceLocation &entry){
            qDebug() <<  "remoteObjectRemoved";
    });
}

void ControlCenterRPC::justtest()
{
    qDebug() << "justtest 11111111111" ;
}
