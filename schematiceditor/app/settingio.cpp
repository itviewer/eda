#include "settingio.h"
#include "schematiceditor.h"
#include "defaultproperty.h"
#include <QStandardPaths>

SettingIO::SettingIO(QObject *parent)
    : QObject(parent)
{
    initEnvironment();
    initSetting();
}

bool SettingIO::saveSchSetting()
{
    return saveJsonDocument(schSettingFile,schSetting);
}

void SettingIO::initEnvironment()
{
    settingDir = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + DS;
    schSettingFile = settingDir + schSettingFileName;

    QDir dir;
    if (!dir.exists(settingDir))
        dir.mkdir(settingDir);
}

void SettingIO::initSetting()
{
    if(!QFileInfo::exists(schSettingFile)){
        generateDefaultSchSetting();
    }

    loadJsonDocument(schSettingFile,schSetting);

    schColorScheme = schGlobalSettingColorScheme["colorScheme"];
    currentColorScheme = schSettingGeneral["lastUsedColorScheme"].get<QString>();
    schColor = schGlobalSettingColorScheme["schemes"][currentColorScheme.toStdString()];
    //schColor.value("Background")
    //schColor.value("Display")
    //schColor.value("Selection")
    //schColor.value("Drawing")
}

void SettingIO::generateDefaultSchSetting()
{
    QFile::copy(":/default/schsetting.json",schSettingFile);
    QFile::setPermissions(schSettingFile,QFileDevice::WriteOwner);
}
