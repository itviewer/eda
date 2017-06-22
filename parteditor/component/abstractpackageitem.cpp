#include "abstractpackageitem.h"
#include "textitem.h"

AbstractPackageItem::AbstractPackageItem(PartScene *scene, QGraphicsItem *parent)
    :QGraphicsItemPackage(parent),
      partScene(scene)
{
    initial();
    setFlags(ItemIsSelectable | ItemIsFocusable);
    if(parent /*&& (parent->type() == Item::PartItemType)*/){
        isMemberOfPackage = true;
    }else{
        setFlags(ItemIsMovable | ItemIsSelectable | ItemIsFocusable);
    }
}

AbstractPackageItem::~AbstractPackageItem()
{

}

QVariant AbstractPackageItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
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

void AbstractPackageItem::initial()
{
    normalPen   = QPen(QColor(schColor.display), 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
    selectedPen = QPen(QColor(schColor.selection), 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
    drawingPen  = QPen(QColor(schColor.drawing), 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

//    setAcceptHoverEvents(true);

    if (partScene->sceneState == FSM::SelectState)
    {
        //TODO 评估是否有必要每次setpen时重绘
        setPen(normalPen);
    }
    else
    {
        setPen(drawingPen);
    }
}
