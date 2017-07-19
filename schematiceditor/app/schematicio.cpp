#include "schematicio.h"
#include "schematiceditor.h"
//#include "schematicview.h"
#include "schematicscene.h"

#include <QFile>
#include <QFileDialog>
#include <QDebug>

SchematicIO::SchematicIO(QObject *parent)
    : QObject(parent)
{

}

bool SchematicIO::loadSchematic(const QString &filename,json &j,const JsonFormat &format) const
{
    json tmp;
    bool success = loadJsonDocument(filename,tmp,format);
    if(success){
        // schProperty 等引用不能重新绑定引用对象 只能重新赋值子属性
        // 要想直接使用子属性 复制一次无法避免
        schProperty = tmp["schProperty"];
        schPinLib = tmp["schPinLib"];
        schPowerLib = tmp["schPowerLib"];
        schOffpageLib = tmp["schOffpageLib"];
        schPartLib = tmp["schPartLib"];
        pages = tmp["pages"];
    }
    return success;
}

bool SchematicIO::saveSchematic(const JsonFormat &format) const
{
    QString filename = schProperty["savePath"];
    // 文件第一次保存或另存
    if(filename.isEmpty()){
        filename = QFileDialog::getSaveFileName(schEditor,"保存原理图", "H:/eda/eda/specification", "原理图文件 (*.json *.sch)");
        if(filename.isEmpty()){
            return false;
        }
        schProperty["savePath"] = filename;
    }else{
        schProperty["modifiedTime"] = QDateTime::currentSecsSinceEpoch();
    }

//    schematic["schProperty"] = schProperty;

    for(auto i = schPages.constBegin();i != schPages.constEnd();i++){
        pages[i.key().toStdString()] = i.value()->getSavedMetadata();
    }

    return saveJsonDocument(filename,schematic,format);
}
