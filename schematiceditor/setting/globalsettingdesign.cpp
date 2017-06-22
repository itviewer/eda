#include "globalsettingdesign.h"
#include "ui_globalsettingdesign.h"

GlobalSettingDesign::GlobalSettingDesign(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GlobalSettingDesign)
{
    ui->setupUi(this);
}

GlobalSettingDesign::~GlobalSettingDesign()
{
    delete ui;
}
