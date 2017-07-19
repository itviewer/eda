#include "cubicbezieritem.h"
#include "cubicbezieritemcontrolpoint.h"

//#include "shapeitemaddcommand.h"
//#include "shapeitemremovecommand.h"
//#include "shapeitemmovecommand.h"
//#include "shapeitemchanggeometryecommand.h"

#include "partscene.h"

CubicBezierItem::CubicBezierItem(PartScene *scene, QGraphicsItem *parent)
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
    metadata["color"] = schColor.display;
}

CubicBezierItem::CubicBezierItem(PartScene *scene, const json &j, QGraphicsItem *parent)
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
        partScene->removeItem(item);
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

//void CubicBezierItem::createCommandAdd()
//{
//    partScene->pushCommand(new ShapeItemAddCommand(this),true);
//    metadata["geometry"] = metaPolygon;
//}

//void CubicBezierItem::createCommandRemove()
//{
//    partScene->pushCommand(new ShapeItemRemoveCommand(this),true);

//}

//void CubicBezierItem::createCommandMove()
//{
//    partScene->pushCommand(new ShapeItemMoveCommand(this));
//}

//void CubicBezierItem::createCommandChangeGeometry()
//{
//    partScene->pushCommand(new ShapeItemChangeGeometryCommand(this));
//}

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
//        createCommandMove();
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
