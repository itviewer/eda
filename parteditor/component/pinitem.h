#ifndef PINITEM_H
#define PINITEM_H

#include "abstractpackageitem.h"

class TextItem;
class LineItem;

class PinItem : public AbstractPackageItem
{
public:
    PinItem(PartScene *scene,const json &j, QGraphicsItem *parent = nullptr);

    enum {
        Type = Item::PinItemType
    };

    void selected();
    void unselected();

    int type() const;

    QRectF boundingRect() const;
    QPainterPath shape() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setRotation(int angle);
    void setPos(const QPointF &pos);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    TextItem *pinNameItem;
    LineItem *lineItem;
};

#endif // PINITEM_H
