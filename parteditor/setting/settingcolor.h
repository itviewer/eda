#ifndef SETTINGCOLOR_H
#define SETTINGCOLOR_H

#include <QWidget>

namespace Ui {
    class SettingColor;
}

class SettingColor : public QWidget
{
    Q_OBJECT

public:
    explicit SettingColor(QWidget *parent = 0);
    ~SettingColor();

private:
    Ui::SettingColor *ui;
};

#endif // SETTINGCOLOR_H
