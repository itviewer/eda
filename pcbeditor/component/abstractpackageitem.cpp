#include "abstractpackageitem.h"

AbstractPackageItem::AbstractPackageItem(PCBScene *scene, QGraphicsItem *parent)
    :QGraphicsItemPackage(parent),
      pcbScene(scene)
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

//    normalPen   = QPen(QColor(schColor.value("Display")), 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
//    selectedPen = QPen(QColor(schColor.value("Selection")), 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
//    drawingPen  = QPen(QColor(schColor.value("Drawing")), 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

//    setAcceptHoverEvents(true);

    if (pcbScene->sceneState == FSM::SelectState)
    {
        //TODO 评估是否有必要每次setpen时重绘
        setPen(normalPen);
    }
    else
    {
        setPen(drawingPen);
    }
}
