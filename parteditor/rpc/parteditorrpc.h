#ifndef PARTEDITORRPC_H
#define PARTEDITORRPC_H

#include "rep_parteditorrpc_source.h"
#include "rep_controlcenterrpc_replica.h"

class PartEditorRPC : public PartEditorRPCSource
{
    Q_OBJECT
public:
    PartEditorRPC(QRemoteObjectNode *node,QObject *parent = nullptr);

signals:
    void test();
private:
    QSharedPointer<ControlCenterRPCReplica> ptr;
    QRemoteObjectNode *rpcNode;

private slots:
    void xxoo();
};
#endif // PARTEDITORRPC_H
