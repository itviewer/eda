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
    bool success = loadJsonDocument(filename,j,format);
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

    for(auto it = schPages.cbegin();it != schPages.cend();it++){
        pages[it.key().toStdString()] = it.value()->getSavedMetadata();
    }

    return saveJsonDocument(filename,schematic,format);
}
