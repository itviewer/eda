#ifndef GLOBALSETTINGLINEWIDTH_H
#define GLOBALSETTINGLINEWIDTH_H

#include <QWidget>

namespace Ui {
    class GlobalSettingLineWidth;
}

class GlobalSettingLineWidth : public QWidget
{
    Q_OBJECT

public:
    explicit GlobalSettingLineWidth(QWidget *parent = 0);
    ~GlobalSettingLineWidth();

private:
    Ui::GlobalSettingLineWidth *ui;
};

#endif // GLOBALSETTINGLINEWIDTH_H
