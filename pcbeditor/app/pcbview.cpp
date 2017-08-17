#include "pcbview.h"
#include "pcbscene.h"
#include "pcbeditor.h"

#include <QMouseEvent>
#include <QElapsedTimer>

PCBView::PCBView(QWidget *parent)
    :QGraphicsView(parent),
      currentScaleFactor(1.0)

{
//    setFrameStyle(QFrame::NoFrame);
    setBackgroundBrush(QColor("#408080"));
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorViewCenter);

    pcbScene = new PCBScene(this);
    setSceneRect(QRectF(0,0, 5000, 5000));
    setScene(pcbScene);

//    snapToGrid = false;
    displayGridSize = 10;

    connect(pcbEditor,&PCBEditor::sceneStateChanged,this,[this](const FSM &state){
        setDragMode((state == FSM::SelectState ? QGraphicsView::RubberBandDrag
                                                        : QGraphicsView::NoDrag));
    });

//    setRenderHint(QPainter::Antialiasing,true);
}

PCBView::~PCBView()
{
    pcbScene->deleteLater();
}

void PCBView::mousePressEvent(QMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::RightButton && itemsAt(mouseEvent->pos()).isEmpty()){
        originMode = dragMode();
        setDragMode(QGraphicsView::ScrollHandDrag);
    }
    QGraphicsView::mousePressEvent(mouseEvent);
}

void PCBView::mouseMoveEvent(QMouseEvent *mouseEvent)
{
//    qDebug() << hasMouseTracking() ;
    QGraphicsView::mouseMoveEvent(mouseEvent);
}

//void PCBView::mouseReleaseEvent(QMouseEvent *mouseEvent)
//{
//    QGraphicsView::mouseReleaseEvent(mouseEvent);

//}

void PCBView::wheelEvent(QWheelEvent *mouseEvent)
{
    if((mouseEvent->modifiers() & Qt::ControlModifier)){
        qreal factor = transform().m11();
        if(mouseEvent->angleDelta().y() > 0){//放大
            if(factor == 10){
                return;
            }else{
                qreal newFactor = scaleFactor.value(factor);
                scale(newFactor, newFactor);
            }
        }else{
            // 缩小
            if(factor == 0.625){
                return;
            }else{
                qreal newFactor = scaleFactor.values(factor).at(1);
                scale(newFactor, newFactor);
            }
        }
        currentScaleFactor = transform().m11();
        pcbEditor->setScaleStatus(QString("%1%").arg(currentScaleFactor * 100));
    }else{
        QGraphicsView::wheelEvent(mouseEvent);
    }
}

void PCBView::contextMenuEvent(QContextMenuEvent *mouseEvent)
{
    // 确保右键菜单时鼠标下有内容
    if (dragMode() == QGraphicsView::ScrollHandDrag){
        setDragMode(originMode);
    }else{
        QGraphicsView::contextMenuEvent(mouseEvent);
    }
}

void PCBView::drawBackground(QPainter *painter, const QRectF &rect)
{
    // rect 仅需要变化的区域，不是整个背景 最大为viewport 以场景坐标描述
    painter->fillRect(rect, backgroundBrush()); // 设置 QPalette::Base 可以避免调用此函数

    if (currentScaleFactor >= 1)
    {
        QPen pen(QColor("#C0C0C0"), 0);
        painter->setPen(pen);
        /**
         * A QTransform object contains a 3 x 3 matrix.
         *
         * m11 m12 m13
         * m21 m22 m23
         * m31 m32 m33
         *
         * The m31 (dx) and m32 (dy) elements specify horizontal and vertical translation
         * The m11 and m22 elements specify horizontal and vertical scaling
         * The m21 and m12 elements specify horizontal and vertical shearing
         * The m13 and m23 elements specify horizontal and vertical projection
         * The m33 as an additional projection factor.
         *
         */


/////////////// viewport 画点 /////////////////////////////////////////////
        int left = floor(rect.left()/displayGridSize)*displayGridSize;
        int top = floor(rect.top()/displayGridSize)*displayGridSize;

        // 画点阵
//        QVector<QPointF> points;// 内存优化
        QVarLengthArray<QPoint, 800> points; // 速度优化

        for (int x = left; x < rect.right(); x += displayGridSize)
        {
            for (int y = top; y < rect.bottom(); y += displayGridSize)
            {
                points.append(QPoint(x, y));
            }
        }

        //points.data() 指向数据的地址指针 当points.size()大于QVarLengthArray长度时 重新分配内存
        painter->drawPoints(points.data(), points.size());

        // 画方格线
//        QVarLengthArray<QLineF, 100> lines;

//        for (qreal x = left; x < rect.right(); x += displayGridSize)
//            lines.append(QLineF(x, rect.top(), x, rect.bottom()));
//        for (qreal y = top; y < rect.bottom(); y += displayGridSize)
//            lines.append(QLineF(rect.left(), y, rect.right(), y));
//            painter->drawLines(lines.data(), lines.size());
    }
}

QList<QGraphicsItem *> PCBView::itemsAt(const QPoint &pos) const
{
    return items(QRect(pos - QPoint(3,3), QSize(6, 6)));
}
