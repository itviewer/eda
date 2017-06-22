#include "pageborderitem.h"

PageBorderItem::PageBorderItem(SchematicScene *scene, const json &j, QGraphicsItem *parent)
    :AbstractPackageItem(scene,parent)
{

}

int PageBorderItem::type() const
{
    return Type;
}
