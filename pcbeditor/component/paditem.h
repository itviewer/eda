#ifndef PADITEM_H
#define PADITEM_H

#include "apertureitem.h"

class PadItem : public ApertureItem
{
public:
    PadItem(PCBScene *scene,const json &j,QGraphicsItem *parent = nullptr);

    enum {
        Type = Item::PadItemType
    };

    int type() const;
};

#endif // PADITEM_H
