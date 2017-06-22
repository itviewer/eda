#include "parttable.h"
#include "partselector.h"
#include <QHeaderView>

#include <QMessageBox>
#include <QSqlQueryModel>

#include <QElapsedTimer>

#include "db.h"

PartTable::PartTable(PartSelector *selector, QWidget *parent)
    :QTableView(parent),
      partSelector(selector)
{

    partLib = new Db(":memory:","partlib");
    partLib->load("H:/eda/sch.db");

    model = new QSqlQueryModel(this);
    model->setQuery("select partid,partname,footprint from part_parts",partLib->database());

    model->setHeaderData(1, Qt::Horizontal, "元件名称");
    model->setHeaderData(2, Qt::Horizontal, "封装");
    setModel(model);
    setColumnHidden(0,true);

    horizontalHeader()->setStretchLastSection(true);
    verticalHeader()->setHidden(true);

    //    horizontalHeader()->setContentsMargins(10,0,10,0);
    resizeRowsToContents();

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setShowGrid(false);
}

void PartTable::updateModel()
{
    model->setQuery("select partid,partname,footprint from part_parts",partLib->database());
    resizeRowsToContents();
}
