#include "state.h"

State::State(QObject* parent)
    : QObject(parent),
      isDrawing(false),
      firstMousePressScenePoint(QPointF(0,0)),
      mousePressScenePoint(QPointF(0,0)),
      mouseReleaseScenePoint(QPointF(0,0)),
      lastMouseReleaseScenePoint(QPointF(0,0)),
      mouseMoveScenePoint(QPointF(0,0)),
      pcbScene(nullptr)
{

}

bool State::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    return false;
}

bool State::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    return false;
}


bool State::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    return false;
}

bool State::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    return false;
}

bool State::keyPressEvent(QKeyEvent *keyEvent)
{
    return false;
}

void State::cancelDrawing()
{

}
