#include "globalsettinglinewidth.h"
#include "ui_globalsettinglinewidth.h"

GlobalSettingLineWidth::GlobalSettingLineWidth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GlobalSettingLineWidth)
{
    ui->setupUi(this);
}

GlobalSettingLineWidth::~GlobalSettingLineWidth()
{
    delete ui;
}
