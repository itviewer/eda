#include "lineitem.h"
#include "lineitemcontrolpoint.h"

//#include "shapeitemaddcommand.h"
//#include "shapeitemremovecommand.h"
//#include "shapeitemmovecommand.h"
//#include "shapeitemchanggeometryecommand.h"
//#include "shapeitemrotatecommand.h"

#include "pcbscene.h"

LineItem::LineItem(PCBScene* scene, QGraphicsItem* parent)
    : QGraphicsLineItem(parent),
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

LineItem::LineItem(PCBScene* scene, const json& j, QGraphicsItem* parent)
    : QGraphicsLineItem(parent),
      AbstractShapeItem(scene,this)
{

}

LineItem::~LineItem()
{
}

void LineItem::selected()
{
    setPen(selectedPen);
    drawControlPoints();
}

void LineItem::unselected()
{
    setPen(normalPen);
    foreach (QGraphicsItem* item, childItems())
    {
        pcbScene->removeItem(item);
        delete item;
    }
}

int LineItem::type() const
{
    return Type;
}

//void LineItem::createCommandAdd()
//{
//    pcbScene->pushCommand(new ShapeItemAddCommand(this),true);
//    metadata["geometry"] = line();
//}

//void LineItem::createCommandRemove()
//{
//    pcbScene->pushCommand(new ShapeItemRemoveCommand(this),true);
//}

//void LineItem::createCommandMove()
//{
//    pcbScene->pushCommand(new ShapeItemMoveCommand(this));
//}

//void LineItem::createCommandChangeGeometry()
//{
//    pcbScene->pushCommand(new ShapeItemChangeGeometryCommand(this));
//}

//void LineItem::createCommandRotation()
//{
//    pcbScene->pushCommand(new ShapeItemRotateCommand(this));
////    metadata["rotation"] = rotation();
//}

//void LineItem::createCommandGroupRotation()
//{

//}

void LineItem::setGeometry(const json &geometry)
{
    setLine(geometry);
}

QVariant LineItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
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

//void LineItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
//{
////    if(mouseEvent->button() == Qt::LeftButton){

////    }else{

////    }
//    QGraphicsLineItem::mousePressEvent(mouseEvent);
//}

void LineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsLineItem::mouseMoveEvent(mouseEvent);
}

void LineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    // 必须先于父类函数执行 父类函数会重置移动状态
    if(isMoved()){
//        createCommandMove();
    }
    QGraphicsLineItem::mouseReleaseEvent(mouseEvent);
}

void LineItem::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
        case Qt::Key_Space:
    {
        for(QGraphicsItem *item:pcbScene->selectedItems()){
            initialRotations.insert(item,item->rotation());
            item->sequenceRotation();
        }
//        createCommandRotation();
        keyEvent->accept();
    }
        break;
    default:
        QGraphicsLineItem::keyPressEvent(keyEvent);
        break;
    }
}

//void LineItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *menuEvent)
//{
//    QMenu menu;
//    QAction *removeAction = menu.addAction("Remove");
//    QAction *markAction = menu.addAction("Mark");
//    QAction *selectedAction = menu.exec(menuEvent->screenPos());
//}

void LineItem::drawControlPoints()
{
    const QLineF &metaLine = line();
    for (int i = 0; i < 2; i++)
    {
        LineItemControlPoint* controlPoint = new LineItemControlPoint(this);
        controlPoint->setPos(metaLine.pointAt(i));
        controlPoint->flag = i;
    }
}

void LineItem::initial()
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
