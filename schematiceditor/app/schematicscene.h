#ifndef SCHEMATICSCENE_H
#define SCHEMATICSCENE_H

#include <QGraphicsScene>
#include "global.h"
#include "defaultproperty.h"

class QUndoStack;

class SchematicView;
class ItemUndoCommand;
class WireUndoCommand;
class Wire;
class JunctionItem;
class RectItem;

class SchematicScene : public QGraphicsScene
{
    Q_OBJECT
public:
    SchematicScene(SchematicView *schView,QObject *parent = nullptr);
    ~SchematicScene();

    bool editingMode;
    int selectedItemsCount;

    SchematicView *schView;

    QUndoStack* undoStack;
    FSM sceneState;

    /**
     * ***********************************************************************
     *
     * 核心数据结构
     *
     * ***********************************************************************
     */

    RectItem *pageBorderItem;

    QSet<QGraphicsItem *> sceneShape;
    QSet<QGraphicsItem *> sceneText;
    QSet<QGraphicsItem *> scenePixmap;

    // attachedNet wire
    QMultiHash<QString,Wire*> sceneWire;
    QHash<QString,JunctionItem*> sceneJunction;

    // 前缀及其元件
    QMap<QString,PartItem*> scenePart;

    /**
     * ***********************************************************************
     * 核心数据存储结构
     * 无法预知原理图页面结构 数据只能从schematic复制一份
     * 如果整个原理图保存为数据库 每个图形在元件表里有唯一键 则能够在保存时只更新变动的图形数据
     * 否则如果有图形变动则保存时需要保存所有图形数据
     * 使用数据库存储数据会增加复杂度，json数据并不是很庞大，复制的开销应该可以接受
     *
     * ***********************************************************************
     */

    json metadata = json::parse(defaultSchPage);
    json &pageProperty = metadata["pageProperty"];
    json &pageShape = metadata["pageShape"];
    json &pagePart = metadata["pagePart"];
    json &pageWire = metadata["pageWire"];

    QSet<QGraphicsItem *> canBeCopiedItems;

    int tabIndex() const;


    void pushCommand(ItemUndoCommand *cmd,bool runRedo = false);
    void pushCommand(WireUndoCommand *cmd);

    void addShape(QGraphicsItem *shapeItem);
    void removeShape(QGraphicsItem *shapeItem);

    void addPart(PartItem *partItem);
    void removePart(PartItem *partItem);

    void addWire(Wire *wire);
    void removeWire(Wire *wire);
    bool containWire(Wire *wire) const;

    void addJunction(JunctionItem *junctionItem);
    void removeJunction(JunctionItem *junctionItem);

    json &getSavedMetadata();
    bool saveMetaData();

signals:
    void editingModeChanged(bool editing);

public slots:
    void onSceneStateChanged(const FSM &state);
    void onSelectionChanged();
    void onEditingModeChanged(bool editing);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent);

    void keyPressEvent(QKeyEvent* keyEvent);
private:
    inline void removeSelectedItems();
    void setPage(const QSizeF &size);

    void saveSceneShape();
    void saveSceneText();
    void saveScenePixmap();

    void saveScenePart();
    void saveSceneWire();
};

#endif // SCHEMATICSCENE_H
