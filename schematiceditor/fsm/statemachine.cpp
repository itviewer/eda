#include "statemachine.h"
#include "schematicscene.h"
#include "schematiceditor.h"
#include <QEvent>
#include <QGraphicsSceneMouseEvent>

#include "stateselect.h"
#include "statelineitem.h"
#include "statepolylineitem.h"
#include "staterectitem.h"
#include "stateroundedrectitem.h"
#include "stateellipseitem.h"
#include "statepolygonitem.h"
#include "statearcitem.h"
#include "statecubicbezieritem.h"
#include "statetextitem.h"
#include "statepixmapitem.h"

#include "statewiresegmentitem.h"
#include "statepartitem.h"

StateMachine::StateMachine(QObject *parent)
    : QObject(parent),
      m_currentState(FSM::SelectState)
{
    states[FSM::SelectState] = new StateSelect(this);
    states[FSM::LineItemState] = new StateLineItem(this);
    states[FSM::PolylineItemState] = new StatePolylineItem(this);
    states[FSM::RectItemState] = new StateRectItem(this);
    states[FSM::RoundedRectItemState] = new StateRoundedRectItem(this);
    states[FSM::EllipseItemState] = new StateEllipseItem(this);
    states[FSM::PolygonItemState] = new StatePolygonItem(this);
    states[FSM::ArcItemState] = new StateArcItem(this);
    states[FSM::CubicBezierItemState] = new StateCubicBezierItem(this);
    states[FSM::TextItemState] = new StateTextItem(this);
    states[FSM::PixmapItemState] = new StatePixmapItem(this);

    states[FSM::WireSegmentItemState] = new StateWireSegmentItem(this);
    states[FSM::PartItemState] = new StatePartItem(this);

}

StateMachine::~StateMachine()
{
    // 如果State不继承QObject且没有父亲 需要手动删除
    //    qDeleteAll(states);
}

State *StateMachine::state(FSM state) const
{
    return states.value(state);
}

FSM StateMachine::currentState() const
{
    return m_currentState;
}

void StateMachine::onSceneStateChanged(FSM state)
{
    m_currentState = state;
    states.value(m_currentState)->schScene = schEditor->currentScene();
}

// 如果不想进一步传递事件 返回true
// 双击会产生 press//release//double click//release 事件序列
bool StateMachine::eventFilter(QObject* obj, QEvent* event)
{
    // 直接返回 不需要 break
    switch (event->type())
    {
        case QEvent::GraphicsSceneMouseMove:
        {
            QGraphicsSceneMouseEvent* mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
            schEditor->setPosStatus(mouseEvent->scenePos());
            return states.value(m_currentState)->mouseMoveEvent(mouseEvent);
        }
        case QEvent::GraphicsSceneMousePress:
        {
            QGraphicsSceneMouseEvent* mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
            return states.value(m_currentState)->mousePressEvent(mouseEvent);
        }
        case QEvent::GraphicsSceneMouseRelease:
        {
            QGraphicsSceneMouseEvent* mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
            return states.value(m_currentState)->mouseReleaseEvent(mouseEvent);
        }
        case QEvent::GraphicsSceneMouseDoubleClick:
        {
            QGraphicsSceneMouseEvent* mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
            return states.value(m_currentState)->mouseDoubleClickEvent(mouseEvent);
        }
        case QEvent::GraphicsSceneContextMenu:
        {
            QGraphicsSceneContextMenuEvent* menuEvent = static_cast<QGraphicsSceneContextMenuEvent*>(event);
            return states.value(m_currentState)->contextMenuEvent(menuEvent);
        }
        case QEvent::KeyPress:
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            return states.value(m_currentState)->keyPressEvent(keyEvent);
        }
    }
    return false;
}
