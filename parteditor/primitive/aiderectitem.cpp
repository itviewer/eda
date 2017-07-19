#include "aiderectitem.h"
#include "aiderectitemcontrolpoint.h"
#include "partscene.h"

AideRectItem::AideRectItem(PartScene *scene, QGraphicsItem *parent)
    :QGraphicsRectItem(parent),
      AbstractShapeItem(scene,this)
{
    initial();
    setFlags(ItemIsSelectable);
}

void AideRectItem::selected()
{
    setPen(selectedPen);
    drawControlPoints();
}

void AideRectItem::unselected()
{
    setPen(normalPen);
    // TODO 考虑不彻底删除 但动态设置AideRectItem大小时会带来控制点位置不对的问题（普通图形不存在该问题）
    for(QGraphicsItem *item:controlPoints) {
        partScene->removeItem(item);
        delete item;
    }
    controlPoints.clear();
}

int AideRectItem::type() const
{
    return Type;
}

QVariant AideRectItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
    case ItemSelectedHasChanged:
        value.toBool() ? selected() : unselected();
        break;
    default:
        break;
    }
    return QGraphicsItem::itemChange(change, value);
}

void AideRectItem::drawControlPoints()
{
    const QRectF &metaRect = rect();
    for(int i=0;i< 4;i++){
        AideRectItemControlPoint *controlPoint = new AideRectItemControlPoint(this);
        controlPoint->setPos(flagToPoint(i,metaRect));
        controlPoint->flag = i;
        controlPoints << controlPoint;
    }
}

void AideRectItem::initial()
{
    normalPen   = QPen(QColor(schColor.display), 0, Qt::DashLine, Qt::SquareCap, Qt::MiterJoin);
    selectedPen = QPen(QColor(schColor.selection), 0, Qt::DashLine, Qt::SquareCap, Qt::MiterJoin);
    drawingPen  = QPen(QColor(schColor.drawing), 0, Qt::DashLine, Qt::SquareCap, Qt::MiterJoin);

    setPen(normalPen);
}
