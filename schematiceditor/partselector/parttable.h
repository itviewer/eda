#ifndef PARTTABLE_H
#define PARTTABLE_H

#include <QTableView>
#include "global.h"

class PartSelector;
class QSqlQueryModel;

class PartTable : public QTableView
{
    Q_OBJECT

public:
    PartTable(PartSelector *selector,QWidget *parent = nullptr);

    void updateModel();

private:
    PartSelector *partSelector;
    QSqlQueryModel *model;
};

#endif // PARTTABLE_H
