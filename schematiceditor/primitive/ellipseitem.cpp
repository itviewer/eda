#include "ellipseitem.h"
#include "ellipseitemcontrolpoint.h"

#include "shapeitemaddcommand.h"
#include "shapeitemremovecommand.h"
#include "shapeitemmovecommand.h"
#include "shapeitemchanggeometryecommand.h"

#include "schematicscene.h"

EllipseItem::EllipseItem(SchematicScene *scene, QGraphicsItem *parent)
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
    metadata["color"] = schColor.value("Display");

}

EllipseItem::EllipseItem(SchematicScene *scene, const json &j, QGraphicsItem *parent)
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
        schScene->removeItem(item);
        delete item;
    }
}

int EllipseItem::type() const
{
    return Type;
}

void EllipseItem::createCommandAdd()
{
    schScene->pushCommand(new ShapeItemAddCommand(this),true);
    metadata["geometry"] = rect();
}

void EllipseItem::createCommandRemove()
{
    schScene->pushCommand(new ShapeItemRemoveCommand(this),true);
}

void EllipseItem::createCommandMove()
{
    schScene->pushCommand(new ShapeItemMoveCommand(this));
}

void EllipseItem::createCommandChangeGeometry()
{
    schScene->pushCommand(new ShapeItemChangeGeometryCommand(this));

}

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
        createCommandMove();

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
    normalPen   = QPen(QColor(schColor.value("Display")), 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
    selectedPen = QPen(QColor(schColor.value("Selection")), 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
    drawingPen  = QPen(QColor(schColor.value("Drawing")), 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

//    setAcceptHoverEvents(true);

    if (schScene->sceneState == FSM::SelectState || schScene->sceneState == FSM::PartItemState)
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
