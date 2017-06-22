#ifndef STATEPIXMAPITEM_H
#define STATEPIXMAPITEM_H

#include "state.h"

class PixmapItem;

class StatePixmapItem : public State
{
public:
    StatePixmapItem(QObject* parent = nullptr);

    bool mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

    bool keyPressEvent(QKeyEvent *keyEvent);

    void cancelDrawing();
private:
    PixmapItem* pixmapItem;
};

#endif // STATEPIXMAPITEM_H
