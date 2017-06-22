#ifndef PARTSELECTOR_H
#define PARTSELECTOR_H

#include <QDockWidget>
#include "global.h"
#include <QModelIndex>

class QLabel;
class QComboBox;
class PartTable;
class PartPreviewer;
class StatePartItem;

class PartSelector : public QDockWidget
{
    Q_OBJECT

public:
    PartSelector(const QString &title, QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

public slots:
    void onPartLibraryChanged();
    void onPartPressed(const QModelIndex &index);
    void onPartDoubleClicked(const QModelIndex &index);

private:
    StatePartItem *statePartItem;
    PartTable *partTable;
    PartPreviewer *partPreviewer;

    QModelIndex previewIndex;

    QLabel *labelPartsValue;
    QComboBox *partSelector;
    QLabel *labelTypeValue;

    int partNumbers;

    void createPart(bool newPart,int partIndex = 0);
};

#endif // PARTSELECTOR_H
