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

void SettingIO::initEnvironment()
{
    settingDir = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + DS;

    QDir dir;
    if (!dir.exists(settingDir))
        dir.mkdir(settingDir);
}

void SettingIO::initSetting()
{
    const QString schSettingFile = settingDir + schSettingFileName;
    if(QFileInfo::exists(schSettingFile)){
        json setting;
        loadJsonDocument(schSettingFile,setting);

        schSettingGeneral = setting["general"];
        schGlobalSettingGeneral = setting["globalSettingGeneral"];
        schGlobalSettingDesign = setting["globalSettingDesign"];
        schGlobalSettingText = setting["globalSettingText"];
        schGlobalSettingLineWidth = setting["globalSettingLineWidth"];
        schGlobalSettingColorScheme = setting["globalSettingColorScheme"];
    }else{
        generateDefaultSchSetting(schSettingFile);
    }

    schColor = schGlobalSettingColorScheme["schemes"][schSettingGeneral["lastUsedColorScheme"].get<std::string>()];
}

void SettingIO::generateDefaultSchSetting(const QString &filename)
{
    saveJsonDocument(filename,json::object());
}
