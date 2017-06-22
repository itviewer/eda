#ifndef STATEPOLYLINEITEM_H
#define STATEPOLYLINEITEM_H

#include "state.h"

class PolylineItem;

class StatePolylineItem : public State
{
public:
    StatePolylineItem(QObject* parent = nullptr);

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
    PolylineItem* polylineItem;
    Angle angleMode;

    bool isHorizontalMode;
    QPointF orthogonalPoint;

    QPolygonF metaPolyline;

    QAction *actionMenuEnd;
    QAction *actionMenuCancel;

    QMenu *contextMenu;
    void createContextMenu();
};

#endif // STATEPOLYLINEITEM_H
