#include "ellipseitem.h"
#include "ellipseitemcontrolpoint.h"

//#include "shapeitemaddcommand.h"
//#include "shapeitemremovecommand.h"
//#include "shapeitemmovecommand.h"
//#include "shapeitemchanggeometryecommand.h"

#include "pcbscene.h"

EllipseItem::EllipseItem(PCBScene *scene, QGraphicsItem *parent)
    :QGraphicsEllipseItem(parent),
      AbstractShapeItem(scene,this)
{
    initial();
    if(parent && (parent->type() > Item::PackageItemType)){
        isMemberOfPackage = true;
    }else{
        setFlags(ItemIsMovable | ItemIsSelectable | ItemIsFocusable);
    }

    metadata["type"] = Type;
    metadata["lineStyle"] = LineStyle::SolidLine;
    metadata["lineWidth"] = LineWidth::Normal;
    metadata["fillStyle"] = FillStyle::NoBrush;
    metadata["color"] = schColor.display;

}

EllipseItem::EllipseItem(PCBScene *scene, const json &j, QGraphicsItem *parent)
    :QGraphicsEllipseItem(parent),
      AbstractShapeItem(scene,this)
{

}

EllipseItem::~EllipseItem()
{
}

void EllipseItem::selected()
{
    setPen(selectedPen);
    drawControlPoints();
}

void EllipseItem::unselected()
{
    setPen(normalPen);
    foreach (QGraphicsItem *item, childItems()) {
        pcbScene->removeItem(item);
        delete item;
    }
}

int EllipseItem::type() const
{
    return Type;
}

//void EllipseItem::createCommandAdd()
//{
//    pcbScene->pushCommand(new ShapeItemAddCommand(this),true);
//    metadata["geometry"] = rect();
//}

//void EllipseItem::createCommandRemove()
//{
//    pcbScene->pushCommand(new ShapeItemRemoveCommand(this),true);
//}

//void EllipseItem::createCommandMove()
//{
//    pcbScene->pushCommand(new ShapeItemMoveCommand(this));
//}

//void EllipseItem::createCommandChangeGeometry()
//{
//    pcbScene->pushCommand(new ShapeItemChangeGeometryCommand(this));

//}

void EllipseItem::setGeometry(const json &geometry)
{
    setRect(geometry);
}

QVariant EllipseItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
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

void EllipseItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(isMoved()){
//        createCommandMove();

    }
    QGraphicsEllipseItem::mouseReleaseEvent(mouseEvent);
}

void EllipseItem::drawControlPoints()
{
    const QRectF &metaRect = rect();
    for(int i=0;i<4;i++){
        EllipseItemControlPoint *controlPoint = new EllipseItemControlPoint(this);
        controlPoint->setPos(flagToPoint(i,metaRect));
        controlPoint->flag = i;
    }
}

void EllipseItem::initial()
{
    normalPen   = QPen(QColor(schColor.display), 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
    selectedPen = QPen(QColor(schColor.selection), 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
    drawingPen  = QPen(QColor(schColor.drawing), 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

//    setAcceptHoverEvents(true);

    if (pcbScene->sceneState == FSM::SelectState /*|| pcbScene->sceneState == FSM::PartItemState*/)
    {
        //TODO 评估是否有必要每次setpen时重绘
        setPen(normalPen);
    }
    else
    {
        setPen(drawingPen);
    }

    setZValue(ZValue::BaseItemZValue);
}
