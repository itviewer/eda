#ifndef PAGEBORDERITEM_H
#define PAGEBORDERITEM_H

#include "abstractpackageitem.h"

class PageBorderItem : public AbstractPackageItem
{
public:
    PageBorderItem(SchematicScene *scene, const json &j, QGraphicsItem *parent);

    enum {
        Type = Item::PageBorderItemType
    };

    int type() const;
};

#endif // PAGEBORDERITEM_H
