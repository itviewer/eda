#include "paditem.h"

PadItem::PadItem(PCBScene *scene, const json &j, QGraphicsItem *parent)
    :ApertureItem(scene,j,parent)
{

}

int PadItem::type() const
{
    return Type;
}
