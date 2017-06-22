#include "stateselect.h"

StateSelect::StateSelect(QObject *parent)
    :State(parent)
{

}

bool StateSelect::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    return false;
}

bool StateSelect::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    return false;
}

bool StateSelect::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    return false;
}

bool StateSelect::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    return false;
}

bool StateSelect::keyPressEvent(QKeyEvent *keyEvent)
{
    return false;
}
