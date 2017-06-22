#include "navigator.h"
#include "schematicnavigator.h"
#include "parttypenavigator.h"
#include "partnavigator.h"
#include "schtreewidgetitem.h"
#include "netnavigator.h"

#include "schematicscene.h"

#include "global.h"

Navigator::Navigator(QWidget *parent)
    :QTreeWidget(parent)
{
    resize(150,0);
    setHeaderHidden(true);
    connect(this,&Navigator::currentItemChanged,this,&Navigator::onCurrentItemChanged);
}

Navigator::~Navigator()
{

}

void Navigator::addSchPage(SchematicScene *scene)
{
    schPageTree.append(new SchTreeWidgetItem(scene,schNavigator));
    schNavigator->sortChildren(1,Qt::AscendingOrder);
}

void Navigator::removeSchPage(const QString &pageName)
{

}

int Navigator::getMaxSchPageIndex()
{
    if(schNavigator->children.isEmpty()){
        return -1;
    }else{
        return schNavigator->children.last()->data(1,Qt::DisplayRole).toInt();
    }
}

QSize Navigator::sizeHint() const
{
    return size();
}

void Navigator::createNavigator()
{
    createSchPageTree();
    createPartTypeTree();
    createPartTree();
    createNetTree();
}

void Navigator::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

void Navigator::onCurrentItemChanged(QTreeWidgetItem *item)
{
    item->selected();
}

//void Navigator::onSchPageAdded()
//{

//}

void Navigator::createSchPageTree()
{
    schNavigator = new SchematicNavigator(QStringList({"原理图"}));
    addTopLevelItem(schNavigator);
}

void Navigator::createPartTypeTree()
{
    partTypeNavigator = new PartTypeNavigator(QStringList({"元件类型"}));
    addTopLevelItem(partTypeNavigator);
}

void Navigator::createPartTree()
{
    partNavigator = new PartNavigator(QStringList({"元件"}));
    addTopLevelItem(partNavigator);
}

void Navigator::createNetTree()
{
    netNavigator = new NetNavigator(QStringList({"网络"}));
    addTopLevelItem(netNavigator);

}
