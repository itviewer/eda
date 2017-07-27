#include "roundedrectitem.h"
#include "roundedrectitemcontrolpoint.h"

#include "shapeitemaddcommand.h"
#include "shapeitemremovecommand.h"
#include "shapeitemmovecommand.h"
#include "shapeitemchanggeometryecommand.h"

#include "schematicscene.h"

RoundedRectItem::RoundedRectItem(SchematicScene *scene, QGraphicsItem *parent)
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
    metadata["color"] = schColor.value("Display");

}

RoundedRectItem::RoundedRectItem(SchematicScene *scene, const json &j, QGraphicsItem *parent)
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
//    if(is2DLine || schScene->isPartEditorMode){
        drawControlPoints();
//    }
}

void RoundedRectItem::unselected()
{
    setPen(normalPen);
//    if(is2DLine || schScene->isPartEditorMode){
        for(QGraphicsItem *item:childItems()) {
            schScene->removeItem(item);
            delete item;
        }
//    }
}

int RoundedRectItem::type() const
{
    return Type;
}

void RoundedRectItem::createCommandAdd()
{
    schScene->pushCommand(new ShapeItemAddCommand(this),true);
    metadata["geometry"]["rect"] = rect();
    metadata["geometry"]["xRadius"] = xRadius();
    metadata["geometry"]["yRadius"] = yRadius();
    metadata["geometry"]["mode"] = mode();
}

void RoundedRectItem::createCommandRemove()
{
    schScene->pushCommand(new ShapeItemRemoveCommand(this),true);

}

void RoundedRectItem::createCommandMove()
{
    schScene->pushCommand(new ShapeItemMoveCommand(this));
}

void RoundedRectItem::createCommandChangeGeometry()
{
    schScene->pushCommand(new ShapeItemChangeGeometryCommand(this));
}

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
        createCommandMove();
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
