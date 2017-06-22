#ifndef STATEPOLYGONITEM_H
#define STATEPOLYGONITEM_H

#include "state.h"

class PolygonItem;

class StatePolygonItem : public State
{
public:
    StatePolygonItem(QObject* parent = nullptr);

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
    PolygonItem* polygonItem;
    bool isOrthogonalMode;

    bool isHorizontalMode;
    QPointF orthogonalPoint;

    QPolygonF metaPolygon;

    QAction *actionMenuEnd;
    QAction *actionMenuCancel;

    QMenu *contextMenu;
    void createContextMenu();
};

#endif // STATEPOLYGONITEM_H
