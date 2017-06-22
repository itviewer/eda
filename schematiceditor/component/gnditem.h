#ifndef GNDITEM_H
#define GNDITEM_H

#include "abstractpackageitem.h"

class TextItem;

class GndItem : public AbstractPackageItem
{
public:
    GndItem(SchematicScene *scene,const json &j,QGraphicsItem *parent = nullptr);

    enum {
        Type = Item::GndItemType
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

#endif // GNDITEM_H
