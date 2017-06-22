#ifndef NETNAVIGATOR_H
#define NETNAVIGATOR_H

#include <QTreeWidgetItem>

class NetNavigator : public QTreeWidgetItem
{
public:
    NetNavigator(const QStringList &strings);

    void selected();
};

#endif // NETNAVIGATOR_H
