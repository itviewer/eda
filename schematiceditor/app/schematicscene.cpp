#include "schematicscene.h"
#include "schematiceditor.h"
#include "schematicview.h"
#include "tabcontainer.h"
#include "schematicio.h"

#include "partitem.h"
#include "wire.h"
#include "junctionitem.h"
#include "wiresegmentitem.h"

#include "itemundocommand.h"
#include "wireundocommand.h"
#include "wiresegmentitemmergecommand.h"

#include <QUndoStack>
#include <QUndoGroup>
#include <QAction>
#include <QKeyEvent>

#include <QElapsedTimer>
#include "rectitem.h"

#include "statemachine.h"

SchematicScene::SchematicScene(SchematicView *schView, QObject *parent)
    :QGraphicsScene(parent),
      editingMode(false),
      schView(schView),
      selectedItemsCount(0)
{
    // 安装事件过滤器给状态机
    installEventFilter(fsm);
    //    setBspTreeDepth();
    undoStack = new QUndoStack(schEditor->undoGroup);
    // undoStack 改变进入编辑模式 保存退出编辑模式
    connect(undoStack,&QUndoStack::indexChanged,this,[this](){
        // 避免关闭程序栈被清空时发射信号
        if(!editingMode && undoStack->count()){
            emit editingModeChanged(true);
        }
    });

    //TODO 关闭程序时亦会触发
    connect(this,&SchematicScene::selectionChanged,
            this,&SchematicScene::onSelectionChanged);

    connect(this,&SchematicScene::editingModeChanged,
            this,&SchematicScene::onEditingModeChanged);

    setPage(pageSizeOption.value(defaultPageSize));
}

SchematicScene::~SchematicScene()
{
    disconnect();
//    disconnect(SIGNAL(selectionChanged()));
}

int SchematicScene::tabIndex() const
{
    return schEditor->tabContainer->indexOf(schView);
}

void SchematicScene::pushCommand(ItemUndoCommand *cmd, bool runRedo)
{
    if(!mergeQueue.isEmpty()){
        for(WireSegmentItem *item:mergeQueue){
            postChildCommands.append(new WireSegmentItemMergeCommand(item));
        }
        mergeQueue.clear();
    }

    if(!preChildCommands.isEmpty()){
        cmd->prependChildCommand(preChildCommands);
        preChildCommands.clear();
    }
    if(!postChildCommands.isEmpty()){
        cmd->appendChildCommand(postChildCommands);
        postChildCommands.clear();
    }

    undoStack->push(cmd,runRedo);
}

void SchematicScene::pushCommand(WireUndoCommand *cmd)
{
    if(!preChildCommands.isEmpty()){
        cmd->prependChildCommand(preChildCommands);
        preChildCommands.clear();
    }
    if(!postChildCommands.isEmpty()){
        cmd->appendChildCommand(postChildCommands);
        postChildCommands.clear();
    }
    undoStack->push(cmd);
}

void SchematicScene::addShape(QGraphicsItem *shapeItem)
{
    sceneShape.insert(shapeItem);
    addItem(shapeItem);
}

void SchematicScene::removeShape(QGraphicsItem *shapeItem)
{
    sceneShape.remove(shapeItem);
    removeItem(shapeItem);
}

void SchematicScene::addPart(PartItem *partItem)
{
    scenePart.insert(partItem->partReference,partItem);

    partTypePart.insert(partItem->partMd5,partItem);

    // 缓存元件库 有必要查找？
    if (schPartLib.find(partItem->partMd5.toStdString()) == schPartLib.end()) {
        schPartLib[partItem->partMd5.toStdString()] = currentPart;
    }
}

void SchematicScene::removePart(PartItem *partItem)
{
    scenePart.remove(partItem->partReference);

    partTypePart.remove(partItem->partMd5,partItem);

    // 只有真正删除才需要在缓存中移除
//    if(!partTypePart.contains(partItem->partMd5)){
//        schPartLib.erase(partItem->partMd5.toStdString());
//    }
}

void SchematicScene::addWire(Wire *wire)
{
    sceneWire.insert(wire->attachedNet(),wire);
}

void SchematicScene::removeWire(Wire *wire)
{
    sceneWire.remove(wire->attachedNet(),wire);
}

bool SchematicScene::containWire(Wire *wire) const
{
    return sceneWire.contains(wire->attachedNet(),wire);
}

void SchematicScene::addJunction(JunctionItem *junctionItem)
{
    sceneJunction.insert(junctionItem->reference,junctionItem);
}

void SchematicScene::removeJunction(JunctionItem *junctionItem)
{
    sceneJunction.remove(junctionItem->reference);
}

json &SchematicScene::getSavedMetadata()
{
    return metadata;
}

void SchematicScene::onSceneStateChanged(const FSM &state)
{
    sceneState = state;
//    if(state != FSM::SelectState){
//        clearSelection();
//    }
}

void SchematicScene::onSelectionChanged()
{
    selectedItemsCount = selectedItems().count();

    canBeCopiedItems.clear();
    for(QGraphicsItem *item:selectedItems()){
        if(!item->isMemberOfPackage){
            canBeCopiedItems.insert(item);
        }
    }

    bool hasSelectedItem = canBeCopiedItems.isEmpty();
    schEditor->actionButtonCopy->setDisabled(hasSelectedItem);
    schEditor->actionButtonCut->setDisabled(hasSelectedItem);
}

void SchematicScene::onEditingModeChanged(bool editing)
{
    editingMode = editing;
    schEditor->tabContainer->changeEditingStatus(editing,tabIndex());
    if(!editing){
        clearSelection();

        // 一旦保存丢弃撤销栈
//        undoStack->clear();
    }
}

void SchematicScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void SchematicScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void SchematicScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void SchematicScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);

}

void SchematicScene::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
    case Qt::Key_Backspace:
    case Qt::Key_Delete:
        removeSelectedItems();
        break;
    default:
        break;
    }
    QGraphicsScene::keyPressEvent(keyEvent);
}

void SchematicScene::removeSelectedItems()
{
    for(QGraphicsItem *item:selectedItems()){
//        removeItem(item);
        item->createCommandRemove();
//        delete item;
    }
    //先执行onSelectionChanged 槽函数再往下执行
    //    qDebug() <<selectedItems();
}

void SchematicScene::setPage(const QSizeF &size)
{
    qreal x = -(maxPageWidth - size.width())/2;
    qreal y = -(maxPageHeight - size.height())/2;

    setSceneRect(x,y,maxPageWidth,maxPageHeight);

    pageBorderItem = new RectItem(this);
    pageBorderItem->setPos(0,0);
    pageBorderItem->setRect(0,0,size.width(),size.height());
    pageBorderItem->setFlags(QGraphicsItem::ItemIgnoresParentOpacity);

    addItem(pageBorderItem);

    pageProperty["sceneRect"] = {x,y,maxPageWidth,maxPageHeight};
}

bool SchematicScene::saveMetaData()
{
    if(editingMode){
        saveSceneShape();
        saveSceneText();
        saveScenePixmap();
        saveScenePart();
    }
    return editingMode;
}

void SchematicScene::saveSceneShape()
{
    pageShape.clear();
    for(QGraphicsItem *item:sceneShape){
        pageShape.push_back(item->getMetadata());
    }
}

void SchematicScene::saveSceneText()
{

}

void SchematicScene::saveScenePixmap()
{

}

void SchematicScene::saveScenePart()
{
    pagePart.clear();
    auto i = scenePart.cbegin();
    while(i != scenePart.cend()){
        pagePart.push_back(i.value()->getMetadata());
        i++;
    }
}

void SchematicScene::saveSceneWire()
{
    pageWire.clear();

}
