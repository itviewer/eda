#ifndef PARTLIBMANAGER_H
#define PARTLIBMANAGER_H

#include <QWidget>
#include "global.h"

namespace Ui {
    class PartLibManager;
}

class QSqlQueryModel;

class PartLibManager : public QWidget
{
    Q_OBJECT

public:
    explicit PartLibManager(QWidget *parent = nullptr);
    ~PartLibManager();

signals:
    void partLibraryChanged();
private slots:
    void onButtonAddLibraryClicked();
    void onButtonRemoveLibraryClicked();
    void onButtonSearchClicked();

private:
    Ui::PartLibManager *ui;

    QSqlQueryModel *model;
    int currentLibIndex;

    void updatePartLibrary();
    void updatePartList(const QString &where = "");
    QString getWhere() const;
};

#endif // PARTLIBMANAGER_H
