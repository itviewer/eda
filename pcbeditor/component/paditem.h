#ifndef PADITEM_H
#define PADITEM_H

#include <QGraphicsPathItem>

class PCBScene;

class PadItem : public QGraphicsPathItem
{
public:
    PadItem(PCBScene *scene, QGraphicsItem *parent = nullptr);
};

#endif // PADITEM_H
