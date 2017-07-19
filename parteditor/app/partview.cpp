#include "partview.h"
#include "partscene.h"
#include "parteditor.h"

#include "packagescene.h"

#include <QMouseEvent>

PartView::PartView(QWidget *parent)
    :QGraphicsView(parent),
      currentScaleFactor(1.0)
{
    gridSize = designGridSize;

    setBackgroundBrush(QColor("#408080"));

    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    setResizeAnchor(QGraphicsView::AnchorViewCenter);

    setSceneRect(0,0,maxSceneWidth,maxSceneHeight);
    connect(partEditor->actionButtonSnapToGrid,&QAction::triggered,this,[this](bool snap){
        snapToGrid = snap;
    });
    connect(partEditor,&PartEditor::sceneStateChanged,this,[this](const FSM &state){
        setDragMode((state == FSM::SelectState ? QGraphicsView::RubberBandDrag
                                                        : QGraphicsView::NoDrag));
    });

    connect(partEditor,&PartEditor::partNumberChanged,this,&PartView::onPartNumberChanged);

    setMouseTracking(true);
}

PartView::~PartView()
{
}

void PartView::zoomIn()
{
    if(currentScaleFactor == 10){
        return;
    }else{
        qreal newFactor = scaleFactor.value(currentScaleFactor);
        if(newFactor){
            scale(newFactor, newFactor);
        }else{
            QList<qreal> factors
            {
                0.1,0.2,0.4,0.5,0.64,0.8,1.0,2.0,4.0,5.0,6.4,8.0,10.0
            };

            factors << currentScaleFactor;
            qSort(factors.begin(), factors.end());

            if(currentScaleFactor != factors.last()){
                newFactor = factors.at(factors.indexOf(currentScaleFactor) + 1);

                QTransform oldMatrix = transform();
                QTransform matrix;
                // 不考虑视图旋转和斜切变换
                matrix.translate(oldMatrix.dx(),oldMatrix.dy());
                matrix.scale(newFactor, newFactor);
                setTransform(matrix);
            }
        }
    }
    currentScaleFactor = int(transform().m11() * 100) / 100.0;
//    partEditor->setScaleStatus(QString("%1%").arg(currentScaleFactor * 100,0,'g',4));

    resetGridSize();
}

void PartView::zoomOut()
{
    if(currentScaleFactor == 0.1){
        return;
    }else{
        QList<qreal> values = scaleFactor.values(currentScaleFactor);
        if(!values.isEmpty()){
            qreal newFactor = values.at(1);
            scale(newFactor, newFactor);
        }else{
            QList<qreal> factors
            {
                0.1,0.2,0.4,0.5,0.64,0.8,1.0,2.0,4.0,5.0,6.4,8.0,10.0
            };

            factors << currentScaleFactor;
            qSort(factors.begin(), factors.end());

            if(currentScaleFactor != factors.first()){
                qreal newFactor = factors.at(factors.indexOf(currentScaleFactor) - 1);
                // 不考虑视图旋转和斜切变换
                QTransform oldMatrix = transform();
                QTransform matrix;
                matrix.translate(oldMatrix.dx(),oldMatrix.dy());
                matrix.scale(newFactor, newFactor);
                setTransform(matrix);
            }
        }
    }
    currentScaleFactor = int(transform().m11() * 100) / 100.0;
//    partEditor->setScaleStatus(QString("%1%").arg(currentScaleFactor * 100,0,'g',4));

    resetGridSize();
}

void PartView::zoomOne()
{
    // 不考虑视图旋转和斜切变换
    QTransform oldMatrix = transform();
    QTransform matrix;
    matrix.translate(oldMatrix.dx(),oldMatrix.dy());
    setTransform(matrix);

    currentScaleFactor = 1.0;
//    partEditor->setScaleStatus(QString("%1%").arg(currentScaleFactor * 100,0,'g',4));

    resetGridSize();
}

void PartView::createNewPart()
{
    if(packageScene){
        qDeleteAll(partScenes);
        partScenes.clear();
        delete packageScene;
    }

    for(int i = 0;i < partNumbers;i++){
        PartScene *scene = new PartScene(this);
        partScenes.append(scene);

        // 能确保第一个场景立即显示
        if(!i){
            partScene = scene;
            setScene(partScene);
        }
    }
    packageScene = new PackageScene(this);

    partEditor->setSceneState(FSM::SelectState);
}

void PartView::mousePressEvent(QMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::RightButton && itemsAt(mouseEvent->pos()).isEmpty()){
        originMode = dragMode();
        setDragMode(QGraphicsView::ScrollHandDrag);
    }
    QGraphicsView::mousePressEvent(mouseEvent);
}

//void PartView::mouseMoveEvent(QMouseEvent *mouseEvent)
//{
//    QGraphicsView::mouseMoveEvent(mouseEvent);
//}

void PartView::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
    QGraphicsView::mouseReleaseEvent(mouseEvent);
    if (dragMode() == QGraphicsView::ScrollHandDrag){
        setDragMode(originMode);
    }
}

void PartView::wheelEvent(QWheelEvent *mouseEvent)
{
    if((mouseEvent->modifiers() & Qt::ControlModifier)){
        if(mouseEvent->delta() > 0){
            //放大
            zoomIn();
        }else{
            // 缩小
            zoomOut();
        }
    }else{
        QGraphicsView::wheelEvent(mouseEvent);
    }
}

void PartView::drawBackground(QPainter *painter, const QRectF &rect)
{
    // rect 仅需要变化的区域，不是整个背景 最大为viewport 以场景坐标描述
    painter->fillRect(rect, backgroundBrush()); // 设置 QPalette::Base 可以避免调用此函数

    if (/*currentScaleFactor == */1)
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

        // 画点阵
/////////////// viewport 画点 /////////////////////////////////////////////
//        int left = int(rect.left()) - (int(rect.left()) % displayGridSize);
//        int top =  int(rect.top()) - (int(rect.top()) % displayGridSize);

        int left = int(rect.left()) - (int(rect.left()) % displayGridSize);
        int top =  int(rect.top()) - (int(rect.top()) % displayGridSize);

//        qreal left = round(rect.left()/displayGridSize)*displayGridSize;
//        qreal top = round(rect.top()/displayGridSize)*displayGridSize;
//        QVector<QPointF> points;// 内存优化
        QVarLengthArray<QPoint, 800> points; // 速度优化

        for (qreal x = left; x < rect.right(); x += displayGridSize)
        {
            for (qreal y = top; y < rect.bottom(); y += displayGridSize)
            {
                points.append(QPoint(x, y));
            }
        }

        //points.data() 指向数据的地址指针 当points.size()大于QVarLengthArray长度时 重新分配内存
        painter->drawPoints(points.data(), points.size());
    }

    // 画方格线
//    qreal left = int(rect.left()) - (int(rect.left()) % displayGridSize);
//    qreal top = int(rect.top()) - (int(rect.top()) % displayGridSize);

//    QVarLengthArray<QLineF, 100> lines;

//    for (qreal x = left; x < rect.right(); x += displayGridSize)
//        lines.append(QLineF(x, rect.top(), x, rect.bottom()));
//    for (qreal y = top; y < rect.bottom(); y += displayGridSize)
//        lines.append(QLineF(rect.left(), y, rect.right(), y));
    //    painter->drawLines(lines.data(), lines.size());
}

void PartView::onPartNumberChanged()
{
    partScene = partScenes.value(currentPartNumber);
    setScene(partScene);
    partEditor->setSceneState(FSM::SelectState);
}

QList<QGraphicsItem *> PartView::itemsAt(const QPoint &pos) const
{
    return items(QRect(pos - QPoint(3,3), QSize(6, 6)));
}

void PartView::resetGridSize()
{
    if(currentScaleFactor == 1.0){
        displayGridSize = 10;
        setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
    }else if(currentScaleFactor < 1.0){
        displayGridSize = 100;
        setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    }
}
