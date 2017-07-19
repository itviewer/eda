#ifndef PARTSCENE_H
#define PARTSCENE_H

#include <QGraphicsScene>
#include "global.h"
#include "defaultproperty.h"

class PartView;
class AideRectItem;

class PartScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PartScene(PartView *partView,QObject *parent = nullptr);

    PartView *partView;

    FSM sceneState;
    AideRectItem *aideRectItem;

    QSet<QGraphicsItem *> sceneShape;
    QSet<QGraphicsItem *> sceneText;
    QSet<QGraphicsItem *> scenePixmap;

    json metadata = json::parse(defaultPart);
    json &partShape = metadata["partShape"];
    json &partText = metadata["partText"];
    json &partPixmap = metadata["partPixmap"];

    void addShape(QGraphicsItem *shapeItem);
    void removeShape(QGraphicsItem *shapeItem);

    void addText(QGraphicsItem *shapeItem);
    void removeText(QGraphicsItem *shapeItem);

    void addPixmap(QGraphicsItem *shapeItem);
    void removePixmap(QGraphicsItem *shapeItem);

    json &getMetadata();
    json &getSavedMetadata();
    bool saveMetaData();

signals:
    void displayGridSizeChanged();
    void shapeAdded();

public slots:
    void onSceneStateChanged(const FSM &state);


private:
    void updateAideRect(QGraphicsItem *shapeItem);
};

#endif // PARTSCENE_H
