#include "statemachine.h"
#include "pcbscene.h"
#include "pcbeditor.h"
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

    PCBScene *pcbScene = pcbEditor->pcbScene();
    for (auto it = states.begin(); it != states.end(); ++it){
        it.value()->pcbScene = pcbScene;
    }
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
    // 必须在cancelDrawing中加入是否正在绘图判断
    // 在状态机中取消绘图会重复调用一次函数 所以不应在状态机响应Key_Escape
    states.value(m_currentState)->cancelDrawing();
    m_currentState = state;
}

// 如果不想进一步传递事件 返回true
// 双击会产生 press//release//double click//release 事件序列
bool StateMachine::eventFilter(QObject* obj, QEvent* event)
{
    // 直接返回 不需要 break
    switch (event->type())
    {
        case QEvent::KeyPress:
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            return states.value(m_currentState)->keyPressEvent(keyEvent);
        }
        case QEvent::GraphicsSceneMousePress:
        {
            QGraphicsSceneMouseEvent* mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
            return states.value(m_currentState)->mousePressEvent(mouseEvent);
        }
        case QEvent::GraphicsSceneMouseMove:
        {
            QGraphicsSceneMouseEvent* mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
            pcbEditor->setPosStatus(mouseEvent->scenePos());
            return states.value(m_currentState)->mouseMoveEvent(mouseEvent);
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
    }
    return false;
}
