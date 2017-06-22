#include "partnavigator.h"
#include "global.h"

PartNavigator::PartNavigator(const QStringList &strings)
    :QTreeWidgetItem(strings,TreeItem::PartNavigatorItem)
{

}

void PartNavigator::selected()
{

}
