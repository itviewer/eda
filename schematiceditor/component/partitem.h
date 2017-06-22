#ifndef PARTITEM_H
#define PARTITEM_H

#include "abstractpackageitem.h"

class PinItem;
class TextItem;

class PartItem : public AbstractPackageItem
{
public:
    PartItem(SchematicScene *scene,int partIndex,QGraphicsItem *parent = nullptr);
    ~PartItem();

    enum {
        Type = Item::PartItemType
    };

    QString reference;
    QString partReference;
    int index;
    QString partIndexA;
    int partIndexN;
    QString partMd5;

    QVector<PinItem*> partPin;

    void selected();
    void unselected();

    int type() const;
//    json &getMetadata() Q_DECL_OVERRIDE;

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setRotation(int angle);

    void setReference(bool increaseIndex);

    void createCommandAdd();
    void createCommandRemove();
    void createCommandMove();

protected:
//    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void keyPressEvent(QKeyEvent *event);
private:
    TextItem *partReferenceItem;

};

#endif // PARTITEM_H
