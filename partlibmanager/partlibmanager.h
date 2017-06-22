#ifndef PARTLIBMANAGER_H
#define PARTLIBMANAGER_H

#include <QWidget>
#include "global.h"

namespace Ui {
    class PartLibManager;
}

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

private:
    Ui::PartLibManager *ui;

    void updatePartLibrary();
};

#endif // PARTLIBMANAGER_H
