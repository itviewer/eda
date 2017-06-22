#ifndef STATECUBICBEZIERITEM_H
#define STATECUBICBEZIERITEM_H

#include "state.h"

class CubicBezierItem;

class StateCubicBezierItem : public State
{
public:
    StateCubicBezierItem(QObject* parent = nullptr);

    bool mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

    bool keyPressEvent(QKeyEvent *keyEvent);

    void cancelDrawing();
private:
    CubicBezierItem* bezierItem;
    QPainterPath bezierPath;
    QPointF ep;

    QPolygonF metaPolygon;
    QPointF cPoint1,cPoint2;

    int flag;
};

#endif // STATECUBICBEZIERITEM_H
