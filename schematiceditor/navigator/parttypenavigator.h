#ifndef PARTTYPENAVIGATOR_H
#define PARTTYPENAVIGATOR_H

#include <QTreeWidgetItem>

class PartTypeNavigator : public QTreeWidgetItem
{
public:
    PartTypeNavigator(const QStringList &strings);

    void selected();
};

#endif // PARTTYPENAVIGATOR_H
