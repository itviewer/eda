#include "schtreewidgetitem.h"
#include "schematicnavigator.h"
#include "schematicscene.h"
#include "schematiceditor.h"
#include "tabcontainer.h"

SchTreeWidgetItem::SchTreeWidgetItem(SchematicScene *scene, SchematicNavigator *parent)
    :QTreeWidgetItem(parent,TreeItem::SchTreeItem),
      schScene(scene)
{
    setText(0,schScene->pageProperty["pageName"]);
    setData(1,Qt::DisplayRole,schScene->pageProperty["index"]);
}

void SchTreeWidgetItem::selected()
{
    schEditor->tabContainer->openSchPage(schScene);
}

