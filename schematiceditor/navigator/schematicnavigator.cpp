#include "schematicnavigator.h"
#include "global.h"

SchematicNavigator::SchematicNavigator(const QStringList &strings)
    :QTreeWidgetItem(strings,TreeItem::SchematicNavigatorItem)
{

}

void SchematicNavigator::selected()
{
    qDebug() << 123 ;
}
