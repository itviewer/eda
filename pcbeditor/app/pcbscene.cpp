#include "pcbscene.h"
#include "pcbeditor.h"

#include <QKeyEvent>

PCBScene::PCBScene(PCBView *pcbView,QObject *parent)
    :QGraphicsScene(parent),
      pcbView(pcbView)
{
}

void PCBScene::onSceneStateChanged(const FSM &state)
{
    sceneState = state;
}

void PCBScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);

}

void PCBScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);

}

void PCBScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);

}

void PCBScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);

}

void PCBScene::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
    case Qt::Key_Escape:
    {
        pcbEditor->setSceneState(FSM::SelectState);
    }
        break;
//    case Qt::Key_Backspace:
//    case Qt::Key_Delete:
//        removeSelectedItems();
//        break;
//    default:
//        break;
    }
    QGraphicsScene::keyPressEvent(keyEvent);

}

void PCBScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *mouseEvent)
{

}
