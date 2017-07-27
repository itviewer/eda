#include "cubicbezieritem.h"
#include "cubicbezieritemcontrolpoint.h"

#include "shapeitemaddcommand.h"
#include "shapeitemremovecommand.h"
#include "shapeitemmovecommand.h"
#include "shapeitemchanggeometryecommand.h"

#include "schematicscene.h"

CubicBezierItem::CubicBezierItem(SchematicScene *scene, QGraphicsItem *parent)
    :QGraphicsPathItem(parent),
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

CubicBezierItem::CubicBezierItem(SchematicScene *scene, const json &j, QGraphicsItem *parent)
    :QGraphicsPathItem(parent),
      AbstractShapeItem(scene,this)
{

}

CubicBezierItem::~CubicBezierItem()
{

}

void CubicBezierItem::selected()
{
    setPen(selectedPen);
    drawControlPoints();
}

void CubicBezierItem::unselected()
{
    setPen(normalPen);
    foreach (QGraphicsItem *item, childItems()) {
        schScene->removeItem(item);
        delete item;
    }
}

int CubicBezierItem::type() const
{
    return Type;
}

QPolygonF CubicBezierItem::getPolygon() const
{
    return metaPolygon;
}

void CubicBezierItem::setPolygon(const QPolygonF &polygon)
{
    metaPolygon = polygon;
}

void CubicBezierItem::createCommandAdd()
{
    schScene->pushCommand(new ShapeItemAddCommand(this),true);
    metadata["geometry"] = metaPolygon;
}

void CubicBezierItem::createCommandRemove()
{
    schScene->pushCommand(new ShapeItemRemoveCommand(this),true);

}

void CubicBezierItem::createCommandMove()
{
    schScene->pushCommand(new ShapeItemMoveCommand(this));
}

void CubicBezierItem::createCommandChangeGeometry()
{
    schScene->pushCommand(new ShapeItemChangeGeometryCommand(this));
}

void CubicBezierItem::setGeometry(const json &geometry)
{
    metaPolygon = geometry;
    QPainterPath tmpPath(metaPolygon.first());

    int size = metaPolygon.size() - 1;
    for(int i = 0; i < size;i+=3){
        tmpPath.cubicTo(metaPolygon.at(i+1),metaPolygon.at(i+2),metaPolygon.at(i+3));
    }
    setPath(tmpPath);
}

QVariant CubicBezierItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
    case ItemSelectedHasChanged:
        value.toBool() ? selected() : unselected();
        break;
    default:
        break;
    }
    return QGraphicsPathItem::itemChange(change,value);
}

void CubicBezierItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(isMoved()){
        createCommandMove();
    }
    QGraphicsPathItem::mouseReleaseEvent(mouseEvent);
}

void CubicBezierItem::drawControlPoints()
{
    int count = metaPolygon.size();
    for(int i=0;i<count;i++){
        CubicBezierItemControlPoint *controlPoint = new CubicBezierItemControlPoint(this);
        controlPoint->setPos(metaPolygon.at(i));
        controlPoint->flag = i;
    }
}

void CubicBezierItem::initial()
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
