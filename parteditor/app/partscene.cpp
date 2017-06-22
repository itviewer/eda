#include "partscene.h"
#include "statemachine.h"

PartScene::PartScene(PartView *partView,QObject *parent)
    :QGraphicsScene(parent),
      partView(partView)
{
    // 安装事件过滤器给状态机
    installEventFilter(fsm);

    connect(this,&PartScene::displayGridSizeChanged,this,[this](){
        qDebug() << 111111111 ;
        update(sceneRect());
    });
}

void PartScene::onSceneStateChanged(const FSM &state)
{
    sceneState = state;
}
