#ifndef STATEROUNDEDRECTITEM_H
#define STATEROUNDEDRECTITEM_H

#include "state.h"

class RoundedRectItem;

class StateRoundedRectItem : public State
{
public:
    StateRoundedRectItem(QObject* parent = nullptr);

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
    RoundedRectItem* rectItem;
    QRectF metaRect;
    qreal radius;

    QAction *actionMenuEnd;
    QAction *actionMenuCancel;

    QMenu *contextMenu;
    void createContextMenu();
};

#endif // STATEROUNDEDRECTITEM_H
