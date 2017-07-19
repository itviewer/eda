#ifndef CONTROLCENTER_H
#define CONTROLCENTER_H

#include <QWidget>

namespace Ui {
    class ControlCenter;
}

class QRemoteObjectRegistryHost;
class QRemoteObjectHost;
class ControlCenterRPC;

class ControlCenter : public QWidget
{
    Q_OBJECT

public:
    explicit ControlCenter(QWidget *parent = 0);
    ~ControlCenter();

private:
    Ui::ControlCenter *ui;

    QRemoteObjectRegistryHost *registryNode;
    QRemoteObjectHost *rpcNode;
    ControlCenterRPC *controlCenterRPC;
};

#endif // CONTROLCENTER_H
