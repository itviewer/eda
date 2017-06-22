#ifndef STATEARCITEM_H
#define STATEARCITEM_H

#include "state.h"

class ArcItem;
class EllipseItem;
class LineItem;

class StateArcItem : public State
{
public:
    StateArcItem(QObject* parent = nullptr);

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
    ArcItem* arcItem;
    EllipseItem* ellipseItem;
    LineItem *lineItem;
    QPainterPath circleArcPath;

    qreal circleArcRadius;
    QRectF metaRect;
    qreal metaStartAngle;
    qreal metaSweepLength;

    QLineF radius;

    QAction *actionMenuEnd;
    QAction *actionMenuCancel;

    QMenu *contextMenu;
    void createContextMenu();
};

#endif // STATEARCITEM_H
