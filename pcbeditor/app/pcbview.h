#ifndef PCBVIEW_H
#define PCBVIEW_H

#include <QGraphicsView>
#include "global.h"


class PCBScene;

class PCBView : public QGraphicsView
{
public:
    PCBView(QWidget *parent = nullptr);
    ~PCBView();

    PCBScene *pcbScene;

protected:
    void mousePressEvent(QMouseEvent *mouseEvent);
    void mouseMoveEvent(QMouseEvent *mouseEvent);
//    void mouseReleaseEvent(QMouseEvent *mouseEvent);
    void wheelEvent(QWheelEvent *mouseEvent);
    void contextMenuEvent(QContextMenuEvent *mouseEvent);

    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    DragMode originMode;
    qreal currentScaleFactor;

    QMultiHash<qreal,qreal> scaleFactor
    {
        {0.625,1.6},
        {1,0.625},
        {1,2},
        {2,0.5},
        {2,2},
        {4,0.5},
        {4,1.25},
        {5,0.8},
        {5,1.6},
        {8,0.625},
        {8,1.25},
        {10,0.8},
        {10,1.5},
//        {15,1/1.5},
//        {15,1.2},
//        {18,1/1.2},
//        {18,0}
    };

    QList<QGraphicsItem *> itemsAt(const QPoint &pos) const;

};

#endif // PCBVIEW_H
