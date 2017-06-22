#ifndef STATEPARTITEM_H
#define STATEPARTITEM_H

#include "state.h"

class PartItem;

class StatePartItem : public State
{
public:
    StatePartItem(QObject* parent = nullptr);

    void createPartItem(bool newPart,int index = 0);
    void createPartItem(int index);
    int currentPartIndex();

    bool mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

    bool contextMenuEvent(QGraphicsSceneContextMenuEvent *menuEvent);
    bool keyPressEvent(QKeyEvent *keyEvent);

    void cancelDrawing();

private:
    PartItem* partItem;
    int partIndex;
    int tmpPartIndex;
    bool increaseIndex;

    QMenu *contextMenu;
    void createContextMenu();
};

#endif // STATEPARTITEM_H
