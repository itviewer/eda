#ifndef GLOBALSETTINGGENERAL_H
#define GLOBALSETTINGGENERAL_H

#include <QWidget>

namespace Ui {
    class GlobalSettingGeneral;
}

class GlobalSettingGeneral : public QWidget
{
    Q_OBJECT

public:
    explicit GlobalSettingGeneral(QWidget *parent = 0);
    ~GlobalSettingGeneral();

private:
    Ui::GlobalSettingGeneral *ui;
};

#endif // GLOBALSETTINGGENERAL_H
