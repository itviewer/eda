#ifndef ABSTRACTPACKAGEITEM_H
#define ABSTRACTPACKAGEITEM_H

#include <QGraphicsItem>
#include <QPen>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "schematicscene.h"
#include "global.h"

class AbstractPackageItem : public QGraphicsItemPackage
{
public:
    AbstractPackageItem(SchematicScene *scene,QGraphicsItem *parent = nullptr);
    ~AbstractPackageItem();

    SchematicScene *schScene;

    QPen drawingPen;
    QPen selectedPen;
    QPen normalPen;

    QRectF shapeRect;

    virtual void selected() = 0;
    virtual void unselected() = 0;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
private:
    inline void initial();
};

static void qt_graphicsItem_highlightSelected(
    AbstractPackageItem *item, QPainter *painter, const QStyleOptionGraphicsItem *option)
{
    Q_UNUSED(option)
    const QRectF murect = painter->transform().mapRect(QRectF(0, 0, 1, 1));
    if (qFuzzyIsNull(qMax(murect.width(), murect.height())))
        return;

    const QRectF mbrect = painter->transform().mapRect(item->boundingRect());
    if (qMin(mbrect.width(), mbrect.height()) < qreal(1.0))
        return;

    qreal itemPenWidth = item->pen().widthF();
    const qreal pad = itemPenWidth / 2;

//    const QColor fgcolor = option->palette.windowText().color();
//    const QColor bgcolor( // ensure good contrast against fgcolor
//        fgcolor.red()   > 127 ? 0 : 255,
//        fgcolor.green() > 127 ? 0 : 255,
//        fgcolor.blue()  > 127 ? 0 : 255);

    // 画背景
    painter->setPen(QPen(Qt::darkBlue, 0, Qt::DashLine));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(item->boundingRect().adjusted(pad, pad, -pad, -pad));

    // 画前景
//    painter->setPen(QPen(option->palette.windowText(), 0, Qt::DashLine));
//    painter->setBrush(Qt::NoBrush);
//    painter->drawRect(item->boundingRect().adjusted(pad, pad, -pad, -pad));
}

#endif // ABSTRACTPACKAGEITEM_H
