#include "rectitem.h"
#include "rectitemcontrolpoint.h"

#include "shapeitemaddcommand.h"
#include "shapeitemremovecommand.h"
#include "shapeitemmovecommand.h"
#include "shapeitemchanggeometryecommand.h"

#include "schematicscene.h"

RectItem::RectItem(SchematicScene *scene, QGraphicsItem *parent)
    :QGraphicsRectItem(parent),
      AbstractShapeItem(scene,this)
{
    initial();
    if(parent && (parent->type() > Item::PackageItemType)){
        isMemberOfPackage = true;
        setFlag(ItemIsMovable,false);
        setFlag(ItemIsSelectable,false);
    }else{
        setFlag(ItemIsMovable,true);
        setFlag(ItemIsSelectable,true);
    }
    setFlag(ItemIsFocusable,true);

    metadata["type"] = Type;
    metadata["lineStyle"] = LineStyle::SolidLine;
    metadata["lineWidth"] = LineWidth::Normal;
    metadata["fillStyle"] = FillStyle::NoBrush;
    metadata["color"] = schColor.display;

//    setFlag(ItemSendsGeometryChanges,true);
}

RectItem::RectItem(SchematicScene *scene, const json &j, QGraphicsItem *parent)
    :QGraphicsRectItem(parent),
      AbstractShapeItem(scene,this)
{
    initial();
    if(parent && (parent->type() > Item::PackageItemType)){
        isMemberOfPackage = true;
    }else{
        setFlags(ItemIsMovable | ItemIsSelectable | ItemIsFocusable);
    }

    metadata = j;
    setPos(j["pos"]);
    setRect(j["geometry"]);
}

RectItem::~RectItem()
{
}

void RectItem::selected()
{
    setPen(selectedPen);
//    if(is2DLine || schScene->isPartEditorMode){
        drawControlPoints();
//    }
}

void RectItem::unselected()
{
    setPen(normalPen);
//    if(is2DLine || schScene->isPartEditorMode){
        for(QGraphicsItem *item:childItems()) {
            schScene->removeItem(item);
            delete item;
        }
//    }
}

int RectItem::type() const
{
    return Type;
}

void RectItem::createCommandAdd()
{
    schScene->pushCommand(new ShapeItemAddCommand(this),true);

    metadata["geometry"] = rect();
}

void RectItem::createCommandRemove()
{
    schScene->pushCommand(new ShapeItemRemoveCommand(this),true);

}

void RectItem::createCommandMove()
{
    schScene->pushCommand(new ShapeItemMoveCommand(this));
}

void RectItem::createCommandChangeGeometry()
{
    schScene->pushCommand(new ShapeItemChangeGeometryCommand(this));
}

void RectItem::setGeometry(const json &geometry)
{
    setRect(geometry);
}

QVariant RectItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
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

void RectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
   QGraphicsRectItem::mouseMoveEvent(mouseEvent);
}

void RectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(isMoved()){
        createCommandMove();
    }
    QGraphicsRectItem::mouseReleaseEvent(mouseEvent);
}

void RectItem::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
        case Qt::Key_Space:
    {
        sequenceRotation();
        keyEvent->accept();
    }
        break;
    default:
        QGraphicsRectItem::keyPressEvent(keyEvent);
        break;
    }
}

void RectItem::drawControlPoints()
{
    const QRectF &metaRect = rect();
    for(int i=0;i< 4;i++){
        RectItemControlPoint *controlPoint = new RectItemControlPoint(this);
        controlPoint->setPos(flagToPoint(i,metaRect));
        controlPoint->flag = i;
    }
}

void RectItem::initial()
{
    normalPen   = QPen(QColor(schColor.display), 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
    selectedPen = QPen(QColor(schColor.selection), 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
    drawingPen  = QPen(QColor(schColor.drawing), 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

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
