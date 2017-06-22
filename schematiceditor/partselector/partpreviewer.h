#ifndef PARTPREVIEWER_H
#define PARTPREVIEWER_H

#include <QGraphicsView>
#include "global.h"

class PartPreviewItem;

class PartPreviewer : public QGraphicsView
{
public:
    PartPreviewer(QWidget *parent =nullptr);

    void setPart(int partIndex);
protected:
//    void wheelEvent(QWheelEvent *event);
private:
    QGraphicsScene *partPreviewScene;
    PartPreviewItem *partPreviewItem;
};

#endif // PARTPREVIEWER_H
