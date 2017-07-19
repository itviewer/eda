#ifndef AIDERECTITEM_H
#define AIDERECTITEM_H


#include <QGraphicsRectItem>

#include "abstractshapeitem.h"

class AideRectItem : public QGraphicsRectItem,public AbstractShapeItem
{
public:
    AideRectItem(PartScene *scene,QGraphicsItem *parent = nullptr);

    enum {
        Type = Item::RectItemType
    };

    QVector<QGraphicsItem *> controlPoints;
    void selected();
    void unselected();

    int type() const;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    void drawControlPoints();
    inline void initial();
};

#endif // AIDERECTITEM_H
