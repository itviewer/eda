#ifndef PARTSCENE_H
#define PARTSCENE_H

#include <QGraphicsScene>
#include "global.h"

class PartView;

class PartScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PartScene(PartView *partView,QObject *parent = nullptr);

    PartView *partView;

    FSM sceneState;

signals:
    void displayGridSizeChanged();
public slots:
    void onSceneStateChanged(const FSM &state);
};

#endif // PARTSCENE_H
