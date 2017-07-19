#include "roundedrectitem.h"
#include "roundedrectitemcontrolpoint.h"

//#include "shapeitemaddcommand.h"
//#include "shapeitemremovecommand.h"
//#include "shapeitemmovecommand.h"
//#include "shapeitemchanggeometryecommand.h"

#include "partscene.h"

RoundedRectItem::RoundedRectItem(PartScene *scene, QGraphicsItem *parent)
    :QGraphicsRoundedRectItem(parent),
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

RoundedRectItem::RoundedRectItem(PartScene *scene, const json &j, QGraphicsItem *parent)
    :QGraphicsRoundedRectItem(parent),
      AbstractShapeItem(scene,this)
{

}

RoundedRectItem::~RoundedRectItem()
{

}

void RoundedRectItem::selected()
{
    setPen(selectedPen);
//    if(is2DLine || partScene->isPartEditorMode){
        drawControlPoints();
//    }
}

void RoundedRectItem::unselected()
{
    setPen(normalPen);
//    if(is2DLine || partScene->isPartEditorMode){
        for(QGraphicsItem *item:childItems()) {
            partScene->removeItem(item);
            delete item;
        }
//    }
}

int RoundedRectItem::type() const
{
    return Type;
}

//void RoundedRectItem::createCommandAdd()
//{
//    partScene->pushCommand(new ShapeItemAddCommand(this),true);
//    metadata["geometry"]["rect"] = rect();
//    metadata["geometry"]["xRadius"] = xRadius();
//    metadata["geometry"]["yRadius"] = yRadius();
//    metadata["geometry"]["mode"] = mode();
//}

//void RoundedRectItem::createCommandRemove()
//{
//    partScene->pushCommand(new ShapeItemRemoveCommand(this),true);

//}

//void RoundedRectItem::createCommandMove()
//{
//    partScene->pushCommand(new ShapeItemMoveCommand(this));
//}

//void RoundedRectItem::createCommandChangeGeometry()
//{
//    partScene->pushCommand(new ShapeItemChangeGeometryCommand(this));
//}

void RoundedRectItem::setGeometry(const json &geometry)
{
    setRect(geometry["rect"]);
}

QVariant RoundedRectItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
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


void RoundedRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(isMoved()){
//        createCommandMove();
    }
    QGraphicsRoundedRectItem::mouseReleaseEvent(mouseEvent);
}

void RoundedRectItem::keyPressEvent(QKeyEvent *keyEvent)
{

}

void RoundedRectItem::drawControlPoints()
{
    const QRectF &metaRect = rect();
    for(int i=0;i< 4;i++){
        RoundedRectItemControlPoint *controlPoint = new RoundedRectItemControlPoint(this);
        controlPoint->setPos(flagToPoint(i,metaRect));
        controlPoint->flag = i;
    }
}

void RoundedRectItem::initial()
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
