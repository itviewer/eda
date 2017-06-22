#include "partpreviewitem.h"
#include "partpreviewer.h"
#include <QPainter>
#include <QGraphicsScene>

PartPreviewItem::PartPreviewItem(PartPreviewer *previewer,QGraphicsItem *parent)
    :QGraphicsItemPackage(parent),
      partPreviewer(previewer)
{
}

int PartPreviewItem::type() const
{
    return Type;
}

QRectF PartPreviewItem::boundingRect() const
{
    if(metadata.size()){
        const QRectF rect = metadata["boundingRect"];
        return rect.adjusted(-5,-5,5,5);;
    }
    return QRectF();
}

void PartPreviewItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(metadata.size()){
        for(auto &shape:metadata["partShape"]){
            switch (int(shape["type"])) {
            case Item::RectItemType:
            {
                drawRect(painter,shape);
            }
                break;
            default:
                break;
            }
        }
//        partPreviewer->fitInView(this);
    }
}

void PartPreviewItem::setMetadata(const json &j)
{
//    prepareGeometryChange();
//    metadata = j;
//    update();
//    partPreviewer->fitInView(this);
}

void PartPreviewItem::drawRect(QPainter *painter, const json &j)
{
//    const QRectF rect = j["geometry"];
//    painter->drawRect(rect);
}
