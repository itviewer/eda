#ifndef APERTUREITEM_H
#define APERTUREITEM_H

#include "abstractpackageitem.h"
#include <QGraphicsPathItem>

class ApertureItem : public AbstractPackageItem
{
public:
    ApertureItem(PCBScene *scene,const json &j,QGraphicsItem *parent = nullptr);

    enum {
        Type = Item::ApertureItemType
    };

    void selected();
    void unselected();

    int type() const;

    QRectF boundingRect() const;
    QPainterPath shape() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setGeometry(const json &geometry);
private:
    QGraphicsPathItem *shapeItem = nullptr;
    QGraphicsPathItem *holeItem = nullptr;
};

#endif // APERTUREITEM_H
