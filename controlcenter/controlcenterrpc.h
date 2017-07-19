#ifndef CONTROLCENTERRPC_H
#define CONTROLCENTERRPC_H

#include "rep_controlcenterrpc_source.h"

class ControlCenterRPC : public ControlCenterRPCSource
{
public:
    ControlCenterRPC(QRemoteObjectNode *node,QObject *parent = nullptr);

public slots:
    void justtest();
private:
    QRemoteObjectNode *registryNode;
};

#endif // CONTROLCENTERRPC_H
