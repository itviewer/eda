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

    bool contextMenuEvent(QGraphicsSceneContextMenuEvent *menuEvent);
    bool keyPressEvent(QKeyEvent *keyEvent);

public slots:
    void cancelDrawing();
    void endDrawing();
private:
    CubicBezierItem* bezierItem;
    QPainterPath bezierPath;
    QPointF ep;

    QPolygonF metaPolygon;
    QPointF cPoint1,cPoint2;

    int flag;

    QAction *actionMenuEnd;
    QAction *actionMenuCancel;

    QMenu *contextMenu;
    void createContextMenu();
};

#endif // STATECUBICBEZIERITEM_H
