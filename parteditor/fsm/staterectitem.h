#ifndef STATERECTITEM_H
#define STATERECTITEM_H

#include "state.h"

class RectItem;

class StateRectItem : public State
{
public:
    StateRectItem(QObject* parent = nullptr);

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
    RectItem* rectItem;
    QRectF metaRect;

    QAction *actionMenuEnd;
    QAction *actionMenuCancel;

    QMenu *contextMenu;
    void createContextMenu();
};

#endif // STATERECTITEM_H
