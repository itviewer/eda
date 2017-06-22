#ifndef STATEELLIPSEITEM_H
#define STATEELLIPSEITEM_H

#include "state.h"

class EllipseItem;

class StateEllipseItem : public State
{
public:
    StateEllipseItem(QObject* parent = nullptr);

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
    EllipseItem* ellipseItem;
    QRectF metaRect;

    QAction *actionMenuEnd;
    QAction *actionMenuCancel;

    QMenu *contextMenu;
    void createContextMenu();
};

#endif // STATEELLIPSEITEM_H
