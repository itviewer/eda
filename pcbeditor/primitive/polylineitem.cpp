#include "polylineitem.h"
#include "polylineitemcontrolpoint.h"

#include "pcbscene.h"

PolylineItem::PolylineItem(PCBScene *scene, QGraphicsItem *parent)
    :QGraphicsPolylineItem(parent),
      AbstractShapeItem(scene,this)
{
    initial();
    if(parent && (parent->type() > Item::PackageItemType)){
        isMemberOfPackage = true;
    }else{
        setFlags(ItemIsMovable | ItemIsSelectable | ItemIsFocusable);
    }


}

PolylineItem::PolylineItem(PCBScene *scene, const json &j, QGraphicsItem *parent)
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
        pcbScene->removeItem(item);
        delete item;
    }
}

int PolylineItem::type() const
{
    return Type;
}

//void PolylineItem::createCommandAdd()
//{
//    pcbScene->pushCommand(new ShapeItemAddCommand(this),true);
//    metadata["geometry"] = polyline();
//}

//void PolylineItem::createCommandRemove()
//{
//    pcbScene->pushCommand(new ShapeItemRemoveCommand(this),true);

//}

//void PolylineItem::createCommandMove()
//{
//    pcbScene->pushCommand(new ShapeItemMoveCommand(this));
//}

//void PolylineItem::createCommandChangeGeometry()
//{
//    pcbScene->pushCommand(new ShapeItemChangeGeometryCommand(this));

//}

//void PolylineItem::setGeometry(const json &geometry)
//{
//    setPolyline(geometry);
//}

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
//    if(isMoved()){
//        createCommandMove();

//    }
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
