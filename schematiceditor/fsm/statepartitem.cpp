#include "statepartitem.h"
#include "partitem.h"

#include "schematicscene.h"
#include "schematicview.h"
#include "schematiceditor.h"

StatePartItem::StatePartItem(QObject *parent)
    : State(parent),
      partItem(nullptr),
      partIndex(-1)
{

}

void StatePartItem::createPartItem(bool newPart,int index)
{
    // 上个元件未结束(如未按ESC)开始画另一个元件
    if(partItem){
        schScene->removeItem(partItem);
        delete partItem;
    }
    createPartItem(index);

    isDrawing = true;
    increaseIndex = newPart;

    if(!schScene->hasFocus()){
       schEditor->setFocusOfCurrentView();
    }
}

void StatePartItem::createPartItem(int index)
{
    tmpPartIndex = index;
    // TODO 默认位置在[0,0] 如果[0,0]在可见区域 不是很友好
    partItem = new PartItem(schScene,tmpPartIndex);
    partItem->hide();
    schScene->addItem(partItem);
}

int StatePartItem::currentPartIndex()
{
    return partIndex;
}

bool StatePartItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton && partItem)
    {
        partItem->setReference(increaseIndex);

        schScene->clearSelection();
        partItem->setSelected(true);

        partItem->createCommandAdd();

        partIndex = tmpPartIndex;

        tmpPartIndex += 1;//还未放置元件的partIndex
        if(tmpPartIndex > int(currentPart["partNumbers"]) - 1){
            increaseIndex = true;
            createPartItem(0);
        }else{
            increaseIndex = false;
            createPartItem(tmpPartIndex);
        }
    }

    return true;
}

bool StatePartItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(partItem){
        partItem->setPos(mouseEvent->scenePos());
        if(!partItem->isVisible()){
            partItem->show();
        }
    }
    return true;
}

bool StatePartItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    return true;
}

bool StatePartItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    return true;
}

bool StatePartItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *menuEvent)
{
    return true;
}

bool StatePartItem::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key())
    {
        case Qt::Key_Escape:
        {
            cancelDrawing();
        }
    }
    return false;
}

void StatePartItem::cancelDrawing()
{
    if(isDrawing){
        schScene->removeItem(partItem);
        delete partItem;
        partItem = nullptr;
        isDrawing = false;
    }
}

void StatePartItem::createContextMenu()
{

}

