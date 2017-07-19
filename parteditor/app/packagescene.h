#ifndef PACKAGESCENE_H
#define PACKAGESCENE_H

#include <QGraphicsScene>
#include "global.h"

class PartView;

class PackageScene : public QGraphicsScene
{
public:
    PackageScene(PartView *partView,QObject *parent = nullptr);

    PartView *partView;
};

#endif // PACKAGESCENE_H
