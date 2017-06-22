#include "globalsettinggeneral.h"
#include "ui_globalsettinggeneral.h"

GlobalSettingGeneral::GlobalSettingGeneral(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GlobalSettingGeneral)
{
    ui->setupUi(this);
}

GlobalSettingGeneral::~GlobalSettingGeneral()
{
    delete ui;
}
