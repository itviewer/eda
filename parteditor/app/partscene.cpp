#include "partscene.h"
#include "statemachine.h"

#include "aiderectitem.h"

PartScene::PartScene(PartView *partView,QObject *parent)
    :QGraphicsScene(parent),
      partView(partView)
{
    // 安装事件过滤器给状态机
    installEventFilter(fsm);

    connect(this,&PartScene::displayGridSizeChanged,this,[this](){
        update(sceneRect());
    });

    aideRectItem = new AideRectItem(this);
    aideRectItem->setPos((maxSceneWidth - 200) / 2,(maxSceneHeight - 200) / 2);
    aideRectItem->setRect(0,0,200,200);

    addItem(aideRectItem);
}

void PartScene::addShape(QGraphicsItem *shapeItem)
{
    updateAideRect(shapeItem);
    sceneShape.insert(shapeItem);
    addItem(shapeItem);
}

void PartScene::removeShape(QGraphicsItem *shapeItem)
{
    sceneShape.remove(shapeItem);
    removeItem(shapeItem);
}

void PartScene::addText(QGraphicsItem *shapeItem)
{

}

void PartScene::removeText(QGraphicsItem *shapeItem)
{

}

void PartScene::addPixmap(QGraphicsItem *shapeItem)
{

}

void PartScene::removePixmap(QGraphicsItem *shapeItem)
{

}

json &PartScene::getMetadata()
{
    return metadata;
}

json &PartScene::getSavedMetadata()
{
    return metadata;
}

bool PartScene::saveMetaData()
{
    return true;
}

void PartScene::onSceneStateChanged(const FSM &state)
{
    sceneState = state;
}

void PartScene::updateAideRect(QGraphicsItem *shapeItem)
{
    QRectF aideRect = aideRectItem->rect() | aideRectItem->mapRectFromItem(shapeItem, shapeItem->boundingRect());
    aideRectItem->setRect(aideRect);
}
