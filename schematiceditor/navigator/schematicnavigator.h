#ifndef SCHEMATICNAVIGATOR_H
#define SCHEMATICNAVIGATOR_H

#include <QTreeWidgetItem>

class SchematicNavigator : public QTreeWidgetItem
{
public:
    SchematicNavigator(const QStringList &strings);

    void selected();
};

#endif // SCHEMATICNAVIGATOR_H
