#include "textitem.h"
#include "partscene.h"

//#include "textitemaddcommand.h"
//#include "textitemremovecommand.h"
//#include "textitemchangepropertycommand.h"
//#include "shapeitemmovecommand.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QKeyEvent>

static void qt_graphicsItem_highlightSelected(
    QGraphicsItem* item, QPainter* painter, const QStyleOptionGraphicsItem* option)
{
    Q_UNUSED(option)
    const QRectF murect = painter->transform().mapRect(QRectF(0, 0, 1, 1));
    if (qFuzzyIsNull(qMax(murect.width(), murect.height())))
        return;

    const QRectF mbrect = painter->transform().mapRect(item->boundingRect());
    if (qMin(mbrect.width(), mbrect.height()) < qreal(1.0))
        return;

    qreal itemPenWidth = static_cast<QGraphicsSimpleTextItem*>(item)->pen().widthF();
    const qreal pad = itemPenWidth / 2;

//    const QColor fgcolor = option->palette.windowText().color();
//    const QColor bgcolor( // ensure good contrast against fgcolor
//        fgcolor.red()   > 127 ? 0 : 255,
//        fgcolor.green() > 127 ? 0 : 255,
//        fgcolor.blue()  > 127 ? 0 : 255);

    // 画背景
    painter->setPen(QPen(Qt::darkBlue, 0, Qt::SolidLine));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(item->boundingRect().adjusted(pad, pad, -pad, -pad));

    // 画前景
//    painter->setPen(QPen(option->palette.windowText(), 0, Qt::DashLine));
//    painter->setBrush(Qt::NoBrush);
//    painter->drawRect(item->boundingRect().adjusted(pad, pad, -pad, -pad));
}

TextItem::TextItem(PartScene* scene, const QString& text, QGraphicsItem* parent)
    : QGraphicsSimpleTextItem(text, parent),
      partScene(scene)
{
//    setBrush(Qt::red);
//    setAcceptHoverEvents(true);
    if (parent && (parent->type() > Item::PackageItemType))
    {
        isMemberOfPackage = true;
//        if (parent->type() == Item::PartItemType)
//        {
//            setFlags(ItemIsSelectable | ItemIsMovable);
//        }
    }
    else
    {
        setFlags(ItemIsSelectable | ItemIsMovable | ItemIsFocusable);
    }
//    setFlag(ItemSendsScenePositionChanges,true);
}

TextItem::~TextItem()
{

}

void TextItem::selected()
{
}

void TextItem::unselected()
{
//    foreach (QGraphicsItem* item, childItems())
//    {
//        partScene->removeItem(item);
//    }
}

int TextItem::type() const
{
    return Type;
}

void TextItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsSimpleTextItem::paint(painter, option, widget);
    if (option->state & QStyle::State_Selected)
    {
        qt_graphicsItem_highlightSelected(this, painter, option);
    }
}

void TextItem::followRotation()
{
    int x = sceneTransform().m11();
    int y = sceneTransform().m12();
//    if(x>=0 && y<=0){
//        setRotation(rotation());qDebug() << 1 << x <<y;
//    }else if(x<0 && y<=0){
//        setRotation((int(rotation()) - 180)%360);qDebug() << 2 << x <<y;
//    }else if (x<=0 && y>0) {
//        setRotation((int(rotation()) - 180)%360);qDebug() << 3 << x <<y;
//    }else{
//        setRotation(rotation());qDebug() << 4 << x <<y;
//    }
    // 仅考虑正交情况
    if(x==0 && y==-1){
        setRotation(rotation());
    }else if(x==-1 && y==0){
        setRotation((int(rotation()) - 180)%360);
    }else if (x==0 && y==1) {
        setRotation((int(rotation()) - 180)%360);
    }else{
        setRotation(rotation());
    }
}

//void TextItem::setText(const QString& text)
//{
//    QGraphicsSimpleTextItem::setText(text);
//    setTransformOriginPoint(boundingRect().center());
//}

//void TextItem::createCommandAdd()
//{
//    partScene->pushCommand(new TextItemAddCommand(this),true);
//}

//void TextItem::createCommandRemove()
//{
//    partScene->pushCommand(new TextItemRemoveCommand(this),true);
//}

//void TextItem::createCommandMove()
//{
//    partScene->pushCommand(new ShapeItemMoveCommand(this));
//}

QVariant TextItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
    switch (change)
    {
        case ItemSelectedHasChanged:
            value.toBool() ? selected() : unselected() ;
            break;
        default:
            break;
    }
    return QGraphicsItem::itemChange(change, value);
}

void TextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(isMoved()){
//        createCommandMove();
    }
    QGraphicsSimpleTextItem::mouseReleaseEvent(mouseEvent);
}


void TextItem::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_Space:
            setRotation(rotation() - 90);
            event->accept();
            break;
        default:
            break;
    }
}
