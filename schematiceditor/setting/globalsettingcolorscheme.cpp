#include "globalsettingcolorscheme.h"
#include "ui_globalsettingcolorscheme.h"

GlobalSettingColorScheme::GlobalSettingColorScheme(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GlobalSettingColorScheme)
{
    ui->setupUi(this);
}

GlobalSettingColorScheme::~GlobalSettingColorScheme()
{
    delete ui;
}
