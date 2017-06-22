#ifndef ArcItemControlPoint_H
#define ArcItemControlPoint_H

#include "abstractcontrolpoint.h"

class ArcItem;

class ArcItemControlPoint : public AbstractControlPoint
{
public:
    ArcItemControlPoint(ArcItem *parent = nullptr);
    ~ArcItemControlPoint();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
private:
    ArcItem *boundingItem;
    QPainterPath boundingItemPath;
    QRectF metaRect;
    qreal metaStartAngle;
    qreal metaSweepLength;
};

#endif // ArcItemControlPoint_H
