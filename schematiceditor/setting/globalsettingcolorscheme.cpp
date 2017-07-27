#include "globalsettingcolorscheme.h"
#include "ui_globalsettingcolorscheme.h"
#include "global.h"
#include <QFormLayout>
#include "newcolorschemedialog.h"
#include "colorselector.h"
#include "settingio.h"

GlobalSettingColorScheme::GlobalSettingColorScheme(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GlobalSettingColorScheme)
{
    ui->setupUi(this);

    QHBoxLayout *hLayout = new QHBoxLayout(ui->groupBoxGraphics);
    QFormLayout *leftGraphicsLayout = new QFormLayout;
    QFormLayout *rightGraphicsLayout = new QFormLayout;
    hLayout->addLayout(leftGraphicsLayout);
    hLayout->addLayout(rightGraphicsLayout);

    QFormLayout *textLayout = new QFormLayout(ui->groupBoxText);

    int i = 0;
    for(const QString &color:colors){
        // 第一列
        if(i < 12){
            ColorSelector *colorSelector = new ColorSelector(schColor.value(color,"#ffffff"),this);
            leftGraphicsLayout->addRow(QString("%1:").arg(color),colorSelector);
            colorMap.insert(color,colorSelector);

            //第二列
        }else if(i < 14){
            ColorSelector *colorSelector = new ColorSelector(schColor.value(color,"#ffffff"),this);
            rightGraphicsLayout->addRow(QString("%1:").arg(color),colorSelector);
            colorMap.insert(color,colorSelector);
        }else{
            ColorSelector *colorSelector = new ColorSelector(schColor.value(color,"#ffffff"),this);
            textLayout->addRow(QString("%1:").arg(color),colorSelector);
            colorMap.insert(color,colorSelector);
        }
        i++;
    }

    for(const QString &scheme:schColorScheme){
        ui->comboBoxColorScheme->addItem(scheme);
    }
    ui->comboBoxColorScheme->setCurrentText(currentColorScheme);

    bool isCustomScheme = ui->comboBoxColorScheme->currentIndex() > -1;
    ui->pushButtonSave->setEnabled(isCustomScheme);
    ui->pushButtonDelete->setEnabled(isCustomScheme);

    adjustSize();
    setFixedSize(size());

    connect(ui->comboBoxColorScheme,&QComboBox::currentTextChanged,this,&GlobalSettingColorScheme::onComboBoxColorSchemeChanged);

    connect(ui->pushButtonSave,&QPushButton::clicked,this,&GlobalSettingColorScheme::onPushButtonSaveClicked);
    connect(ui->pushButtonDelete,&QPushButton::clicked,this,&GlobalSettingColorScheme::onPushButtonDeleteClicked);
    connect(ui->pushButtonSaveAs,&QPushButton::clicked,this,&GlobalSettingColorScheme::createNewColorScheme);

    connect(ui->pushButtonOK,&QPushButton::clicked,this,&GlobalSettingColorScheme::onPushButtonOKClicked);
    connect(ui->pushButtonApply,&QPushButton::clicked,this,&GlobalSettingColorScheme::onPushButtonApplyClicked);
    connect(ui->pushButtonCancel,&QPushButton::clicked,this,&GlobalSettingColorScheme::close);

}

GlobalSettingColorScheme::~GlobalSettingColorScheme()
{
    delete ui;
}

void GlobalSettingColorScheme::showEvent(QShowEvent *event)
{
    ui->comboBoxColorScheme->setCurrentText(currentColorScheme);
    QWidget::showEvent(event);
}

void GlobalSettingColorScheme::createNewColorScheme()
{
    QString schemeName = "";
    if(askColorSchemeName(schemeName)){
        schColorScheme.append(schemeName);

        schGlobalSettingColorScheme["colorScheme"].push_back(schemeName);
        schGlobalSettingColorScheme["schemes"][schemeName.toStdString()] = colorMapToColor();

        ui->comboBoxColorScheme->addItem(schemeName);
        ui->comboBoxColorScheme->setCurrentText(schemeName);

        settingIO->saveSchSetting();
    }
}

void GlobalSettingColorScheme::onComboBoxColorSchemeChanged(const QString &schemeName)
{
//    bool isCustomScheme = ui->comboBoxColorScheme->currentIndex() > 2;
//    ui->pushButtonSave->setEnabled(isCustomScheme);
//    ui->pushButtonDelete->setEnabled(isCustomScheme);

    QHash<QString, QString> color = schGlobalSettingColorScheme["schemes"][schemeName.toStdString()];
    for(auto it = colorMap.cbegin();it != colorMap.cend();it++){
        it.value()->setCurrentColor(color.value(it.key()));
    }
}

void GlobalSettingColorScheme::onPushButtonSaveClicked()
{
    QString schemeName = ui->comboBoxColorScheme->currentText();

    schGlobalSettingColorScheme["schemes"][schemeName.toStdString()] = colorMapToColor();
    settingIO->saveSchSetting();
}

void GlobalSettingColorScheme::onPushButtonDeleteClicked()
{
    const QString schemeName = ui->comboBoxColorScheme->currentText();

    ui->comboBoxColorScheme->removeItem(ui->comboBoxColorScheme->currentIndex());

    schColorScheme.removeOne(schemeName);
    currentColorScheme = ui->comboBoxColorScheme->currentText();
    schColor = schGlobalSettingColorScheme["schemes"][currentColorScheme.toStdString()];

    schSettingGeneral["lastUsedColorScheme"] = currentColorScheme;
    // TODO json没有好的方法删除数组的元素 std::find有些麻烦
    schGlobalSettingColorScheme["colorScheme"] = schColorScheme;
    schGlobalSettingColorScheme["schemes"].erase(schemeName.toStdString());

    settingIO->saveSchSetting();
}

void GlobalSettingColorScheme::onPushButtonOKClicked()
{
    onPushButtonApplyClicked();
    close();
}

void GlobalSettingColorScheme::onPushButtonApplyClicked()
{
    currentColorScheme = ui->comboBoxColorScheme->currentText();
    schColor = colorMapToColor();

    schSettingGeneral["lastUsedColorScheme"] = currentColorScheme;

    settingIO->saveSchSetting();
}

bool GlobalSettingColorScheme::askColorSchemeName(QString &newSchemeName)
{
    NewColorSchemeDialog newColorSchemeDialog;
    newColorSchemeDialog.setColorSchemeName(newSchemeName);
    newColorSchemeDialog.exec();

    if(newColorSchemeDialog.result()){
        newSchemeName = newColorSchemeDialog.colorSchemeName();
        return true;
    }
    return false;
}

QHash<QString, QString> GlobalSettingColorScheme::colorMapToColor()
{
    QHash<QString, QString> color;
    for(auto it = colorMap.cbegin();it != colorMap.cend();it++){
        color.insert(it.key(),it.value()->currentColor());
    }
    return color;
}
