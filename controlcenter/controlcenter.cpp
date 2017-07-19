#include "controlcenter.h"
#include "ui_controlcenter.h"

#include <QRemoteObjectRegistryHost>

#include "controlcenterrpc.h"

ControlCenter::ControlCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlCenter)
{
    ui->setupUi(this);

    registryNode = new QRemoteObjectRegistryHost(QUrl(QStringLiteral("local:RegistryControlCenter")),this);
    rpcNode = new QRemoteObjectHost(QUrl(QStringLiteral("local:ControlCenter")), QUrl(QStringLiteral("local:RegistryControlCenter")),this);

    controlCenterRPC = new ControlCenterRPC(registryNode,this);
    rpcNode->enableRemoting(controlCenterRPC);
}

ControlCenter::~ControlCenter()
{
    delete ui;
}
