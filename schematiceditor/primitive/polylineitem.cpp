#include "polylineitem.h"
#include "polylineitemcontrolpoint.h"

#include "shapeitemaddcommand.h"
#include "shapeitemremovecommand.h"
#include "shapeitemmovecommand.h"
#include "shapeitemchanggeometryecommand.h"


#include "schematicscene.h"

PolylineItem::PolylineItem(SchematicScene *scene, QGraphicsItem *parent)
    :QGraphicsPolylineItem(parent),
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
    metadata["color"] = schColor.value("Display");

}

PolylineItem::PolylineItem(SchematicScene *scene, const json &j, QGraphicsItem *parent)
    :QGraphicsPolylineItem(parent),
      AbstractShapeItem(scene,this)
{

}

PolylineItem::~PolylineItem()
{
}

void PolylineItem::selected()
{
    setPen(selectedPen);
    drawControlPoints();
}

void PolylineItem::unselected()
{
    setPen(normalPen);
    foreach (QGraphicsItem *item, childItems()) {
        schScene->removeItem(item);
        delete item;
    }
}

int PolylineItem::type() const
{
    return Type;
}

void PolylineItem::createCommandAdd()
{
    schScene->pushCommand(new ShapeItemAddCommand(this),true);
    metadata["geometry"] = polyline();
}

void PolylineItem::createCommandRemove()
{
    schScene->pushCommand(new ShapeItemRemoveCommand(this),true);

}

void PolylineItem::createCommandMove()
{
    schScene->pushCommand(new ShapeItemMoveCommand(this));
}

void PolylineItem::createCommandChangeGeometry()
{
    schScene->pushCommand(new ShapeItemChangeGeometryCommand(this));

}

void PolylineItem::setGeometry(const json &geometry)
{
    setPolyline(geometry);
}

QVariant PolylineItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
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

void PolylineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(isMoved()){
        createCommandMove();

    }
    QGraphicsPolylineItem::mouseReleaseEvent(mouseEvent);
}

void PolylineItem::drawControlPoints()
{
    const QPolygonF &metaPolyline = polyline();
    int count = metaPolyline.size();
    for(int i=0;i<count;i++){
        PolylineItemControlPoint *controlPoint = new PolylineItemControlPoint(this);
        controlPoint->setPos(metaPolyline.at(i));
        controlPoint->flag = i;
    }
}

void PolylineItem::initial()
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
