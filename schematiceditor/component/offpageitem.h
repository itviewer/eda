#ifndef OFFPAGEITEM_H
#define OFFPAGEITEM_H

#include "abstractpackageitem.h"

class TextItem;

class OffpageItem : public AbstractPackageItem
{
public:
    OffpageItem(SchematicScene *scene, const json &j, QGraphicsItem *parent);

    enum {
        Type = Item::BusItemType
    };

    void selected();
    void unselected();

    int type() const;

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setRotation(int angle);

protected:
//    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void keyPressEvent(QKeyEvent *event);
private:
    TextItem *valueItem;
};
#endif // OFFPAGEITEM_H
