#include "globalsettingbackup.h"
#include "ui_globalsettingbackup.h"

GlobalSettingBackup::GlobalSettingBackup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GlobalSettingBackup)
{
    ui->setupUi(this);
}

GlobalSettingBackup::~GlobalSettingBackup()
{
    delete ui;
}
