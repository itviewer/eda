#include "partpreviewer.h"
#include "partpreviewitem.h"

#include <QScrollBar>

PartPreviewer::PartPreviewer(QWidget *parent)
    :QGraphicsView(parent)
{
    setFixedSize(115,115);
    setBackgroundBrush(QColor(schColor.value("Background")));
//    setFrameStyle(QFrame::NoFrame);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    partPreviewScene = new QGraphicsScene(this);
    setSceneRect(QRectF(-2500,-2500,5000,5000));
    setScene(partPreviewScene);

    partPreviewItem = new PartPreviewItem(this);
    partPreviewScene->addItem(partPreviewItem);

//    partPreviewItem->setPos(QPointF(1,1));
    //    centerOn(partPreviewItem);
}

void PartPreviewer::setPart(int partIndex)
{

}

//void PartPreviewer::wheelEvent(QWheelEvent *event)
//{
//    Q_UNUSED(event)
//}
