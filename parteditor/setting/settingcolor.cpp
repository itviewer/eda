#include "settingcolor.h"
#include "ui_settingcolor.h"

SettingColor::SettingColor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingColor)
{
    ui->setupUi(this);
}

SettingColor::~SettingColor()
{
    delete ui;
}
