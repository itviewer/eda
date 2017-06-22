#ifndef PARTPREVIEWITEM_H
#define PARTPREVIEWITEM_H

#include <QGraphicsItem>
#include "global.h"

class PartPreviewer;

class PartPreviewItem : public QGraphicsItemPackage
{
public:
    PartPreviewItem(PartPreviewer *previewer,QGraphicsItem *parent = nullptr);

    enum {
        Type = Item::PartPreviewItemType
    };

    int type() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setMetadata(const json &j);
private:
    PartPreviewer *partPreviewer;
    inline void drawRect(QPainter *painter,const json &j);
};

#endif // PARTPREVIEWITEM_H
