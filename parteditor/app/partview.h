#ifndef PARTVIEW_H
#define PARTVIEW_H

#include <QGraphicsView>
#include "global.h"

class PartView : public QGraphicsView
{
public:
    PartView(QWidget *parent = nullptr);
    ~PartView();

    PartScene *partScene;

    void zoomIn();
    void zoomOut();
    void zoomOne();

    void createNewPart();

protected:
    void mousePressEvent(QMouseEvent *mouseEvent);
//    void mouseMoveEvent(QMouseEvent *mouseEvent);
    void mouseReleaseEvent(QMouseEvent *mouseEvent);
    void wheelEvent(QWheelEvent *mouseEvent);

//    void contextMenuEvent(QContextMenuEvent *menuEvent);

    void drawBackground(QPainter *painter, const QRectF &rect);
private slots:
    void onPartNumberChanged();
private:
    DragMode originMode;
    qreal currentScaleFactor;

    QMultiHash<qreal,qreal> scaleFactor
    {
        {0.1,2.0},
        {0.2,0.5},
        {0.2,2.0},
        {0.4,0.5},
        {0.4,1.25},
        {0.5,0.8},
        {0.5,1.28},
        {0.64,0.78125},
        {0.64,1.25},
        {0.8,0.8},
        {0.8,1.25},
        {1.0,0.8},
        {1.0,2.0},
        {2.0,0.5},
        {2.0,2.0},
        {4.0,0.5},
        {4.0,1.25},
        {5.0,0.8},
        {5.0,1.28},
        {6.4,0.78125},
        {6.4,1.25},
        {8.0,0.8},
        {8.0,1.25},
        {10.0,0.8},
        {10.0,1.5},
//        {15,1/1.5},
//        {15,1.2},
//        {18,1/1.2},
//        {18,0}
    };

    QList<QGraphicsItem *> itemsAt(const QPoint &pos) const;
    void resetGridSize();
};

#endif // PARTVIEW_H
