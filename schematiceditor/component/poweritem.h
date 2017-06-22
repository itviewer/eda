#ifndef POWERITEM_H
#define POWERITEM_H

#include "abstractpackageitem.h"

class TextItem;

class PowerItem : public AbstractPackageItem
{
public:
    PowerItem(SchematicScene *scene,const json &j,QGraphicsItem *parent = nullptr);

    enum {
        Type = Item::PowerItemType
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

#endif // POWERITEM_H
