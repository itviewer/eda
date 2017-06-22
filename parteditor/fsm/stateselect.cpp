#include "stateselect.h"
#include <QGraphicsItem>

StateSelect::StateSelect(QObject *parent)
    :State(parent)
{
    createShapeContextMenu();
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

bool StateSelect::contextMenuEvent(QGraphicsSceneContextMenuEvent *menuEvent)
{
    // TODO 这里和视图的itemsAt判断标准不一致导致错误
    QGraphicsItem *item = partScene->itemAt(menuEvent->scenePos());
    if(!item->isSelected()){
        partScene->clearSelection();
        item->setSelected(true);
    }
    int count = partScene->selectedItems().count();
    // 右键菜单必须在有item被选中时触发
    if(count == 1){
        if(item->type() < 110000){
            shapeContextMenu->popup(menuEvent->screenPos());
        }else if(item->type() < 210000){

        }
    }else{

    }

    return true;
}

bool StateSelect::keyPressEvent(QKeyEvent *keyEvent)
{
    return false;
}

void StateSelect::createShapeContextMenu()
{
    shapeContextMenu = new QMenu;
    QAction *actionDelete = shapeContextMenu->addAction("Delete");
    QAction *actionRotate = shapeContextMenu->addAction("Rotate");
}
