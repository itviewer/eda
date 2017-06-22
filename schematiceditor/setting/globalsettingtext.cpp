#include "globalsettingtext.h"
#include "ui_globalsettingtext.h"

GlobalSettingText::GlobalSettingText(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GlobalSettingText)
{
    ui->setupUi(this);
}

GlobalSettingText::~GlobalSettingText()
{
    delete ui;
}
