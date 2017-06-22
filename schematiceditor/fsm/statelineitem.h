#ifndef STATELINEITEM_H
#define STATELINEITEM_H

#include "state.h"

class LineItem;

class StateLineItem : public State
{
public:
    StateLineItem(QObject* parent = nullptr);

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
    LineItem* lineItem;
    QLineF metaLine;

    QAction *actionMenuEnd;
    QAction *actionMenuCancel;

    QMenu *contextMenu;
    void createContextMenu();
};

#endif // STATELINEITEM_H
