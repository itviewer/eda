#include "ellipseitem.h"
#include "ellipseitemcontrolpoint.h"

//#include "shapeitemaddcommand.h"
//#include "shapeitemremovecommand.h"
//#include "shapeitemmovecommand.h"
//#include "shapeitemchanggeometryecommand.h"

#include "PartScene.h"

EllipseItem::EllipseItem(PartScene *scene, QGraphicsItem *parent)
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

EllipseItem::EllipseItem(PartScene *scene, const json &j, QGraphicsItem *parent)
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
        partScene->removeItem(item);
        delete item;
    }
}

int EllipseItem::type() const
{
    return Type;
}

//void EllipseItem::createCommandAdd()
//{
//    partScene->pushCommand(new ShapeItemAddCommand(this),true);
//    metadata["geometry"] = rect();
//}

//void EllipseItem::createCommandRemove()
//{
//    partScene->pushCommand(new ShapeItemRemoveCommand(this),true);
//}

//void EllipseItem::createCommandMove()
//{
//    partScene->pushCommand(new ShapeItemMoveCommand(this));
//}

//void EllipseItem::createCommandChangeGeometry()
//{
//    partScene->pushCommand(new ShapeItemChangeGeometryCommand(this));

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

    if (partScene->sceneState == FSM::SelectState /*|| partScene->sceneState == FSM::PartItemState*/)
    {
        //TODO 评估是否有必要每次setpen时重绘
        setPen(normalPen);
    }
    else
    {
        setPen(drawingPen);
    }

//    setZValue(ZValue::BaseItemZValue);
}
