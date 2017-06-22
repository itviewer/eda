#include "abstractcontrolpoint.h"

#include "pcbscene.h"

AbstractControlPoint::AbstractControlPoint(QGraphicsItem *parent)
    :QGraphicsRectItem(QRectF(-5,-5,10,10),parent)
{
    setPen(Qt::NoPen);
    setBrush(QColor(schColor.selection));
    setFlags( QGraphicsItem::ItemIsMovable |QGraphicsItem::ItemIgnoresTransformations );
}

AbstractControlPoint::~AbstractControlPoint()
{

}
