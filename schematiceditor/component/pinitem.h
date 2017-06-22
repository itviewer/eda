#ifndef PINITEM_H
#define PINITEM_H

#include "abstractpackageitem.h"

class PortItem;
class TextItem;
class LineItem;

class PinItem : public AbstractPackageItem
{
public:
    PinItem(SchematicScene *scene, QGraphicsItem *parent = nullptr);
    PinItem(SchematicScene *scene,const json &j, QGraphicsItem *parent = nullptr);
    ~PinItem();

    PortItem *port;
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

    void setPinName(const json &name);
    void setPinNubmer(const json &number);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void keyPressEvent(QKeyEvent *event);
//    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);

//    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    TextItem *pinNameItem;
    LineItem *lineItem;
};

#endif // PINITEM_H
