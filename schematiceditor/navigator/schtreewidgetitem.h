#ifndef SCHTREEWIDGETITEM_H
#define SCHTREEWIDGETITEM_H

#include <QTreeWidgetItem>

class SchematicNavigator;
class SchematicScene;

class SchTreeWidgetItem : public QTreeWidgetItem
{
public:
    SchTreeWidgetItem(SchematicScene *scene,SchematicNavigator *parent);

    void selected();
private:
    SchematicScene *schScene;
};

#endif // SCHTREEWIDGETITEM_H
