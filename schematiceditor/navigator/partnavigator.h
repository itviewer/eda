#ifndef PARTNAVIGATOR_H
#define PARTNAVIGATOR_H

#include <QTreeWidgetItem>

class PartNavigator : public QTreeWidgetItem
{
public:
    PartNavigator(const QStringList &strings);

    void selected();
};

#endif // PARTNAVIGATOR_H
