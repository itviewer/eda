#ifndef SETTINGGRID_H
#define SETTINGGRID_H

#include <QWidget>

namespace Ui {
    class SettingGrid;
}

class SettingGrid : public QWidget
{
    Q_OBJECT

public:
    explicit SettingGrid(QWidget *parent = 0);
    ~SettingGrid();

protected:
    void showEvent(QShowEvent *event);
private:
    Ui::SettingGrid *ui;

    QStringList gridSizes = {
        "10","50","100","500","1000"
    };
};

#endif // SETTINGGRID_H
