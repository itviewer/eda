#ifndef STATEPINITEM_H
#define STATEPINITEM_H

#include "state.h"

class PinItem;

class StatePinItem : public State
{
public:
    StatePinItem(QObject* parent = nullptr);

    void onEntry(PartScene *scene);
    bool mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
private:
    PinItem* pinItem;

    QRectF aideRect;
    QLineF topLine,rightLine,bottomLine,leftLine;
    float aspectRatio;
};

#endif // STATEPINITEM_H
