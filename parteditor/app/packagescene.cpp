#include "packagescene.h"

PackageScene::PackageScene(PartView *partView, QObject *parent)
    :QGraphicsScene(parent),
      partView(partView)
{

}
