#ifndef WIREADDCOMMAND_H
#define WIREADDCOMMAND_H

#include "wireundocommand.h"

class WireAddCommand : public WireUndoCommand
{
public:
    WireAddCommand(Wire *wire);
    ~WireAddCommand();

    void undo();
    void redo();

private:
    JunctionItem *attachedStartJunction;
    JunctionItem *attachedEndJunction;
    PortItem *attachedStartPort;
    PortItem *attachedEndPort;

    QString netName;
    QString originEndNetName;
};

#endif // WIREADDCOMMAND_H
