#ifndef SETTINGFONT_H
#define SETTINGFONT_H

#include <QWidget>

namespace Ui {
    class SettingFont;
}

class SettingFont : public QWidget
{
    Q_OBJECT

public:
    explicit SettingFont(QWidget *parent = 0);
    ~SettingFont();

private:
    Ui::SettingFont *ui;
};

#endif // SETTINGFONT_H
