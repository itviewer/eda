#include "settingfont.h"
#include "ui_settingfont.h"

SettingFont::SettingFont(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingFont)
{
    ui->setupUi(this);
}

SettingFont::~SettingFont()
{
    delete ui;
}
