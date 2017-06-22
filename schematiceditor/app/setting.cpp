#include "setting.h"
#include "schematiceditor.h"
#include "defaultproperty.h"

Setting::Setting(QObject *parent)
    : QObject(parent)
{
    init();
    connect(schEditor,&SchematicEditor::launched,
            this,&Setting::postInit);
}

void Setting::init()
{
    // 颜色方案需要先解析
    colorSchemes["OrCAD"] = json::parse(colorSchemeOrCAD);
    colorSchemes["Pads"] = json::parse(colorSchemePads);

    schColor = colorSchemes["OrCAD"];
}

void Setting::postInit()
{
}
