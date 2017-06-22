#include "setting.h"
#include "pcbeditor.h"
#include "defaultproperty.h"

Setting::Setting(QObject *parent)
    : QObject(parent)
{
    init();
    initUnitsRatio();
    connect(pcbEditor,&PCBEditor::launch,
            this,&Setting::postInit);
}

void Setting::init()
{
    // 颜色方案需要先解析
    colorSchemes["OrCAD"] = json::parse(colorSchemeOrCAD);
    colorSchemes["Pads"] = json::parse(colorSchemePads);

    schColor = colorSchemes["OrCAD"];
}

void Setting::initUnitsRatio()
{

}

void Setting::postInit()
{
}
