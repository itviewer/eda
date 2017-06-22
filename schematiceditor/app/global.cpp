#include "global.h"
#include <QtMath>
#include "defaultproperty.h"

/**
 * ***********************************************************************
 *
 *  非持久化全局变量
 *
 * ***********************************************************************
 */

bool snapToGrid = true;
colorScheme schColor;

SchematicEditor *schEditor = nullptr;
StateMachine *fsm = nullptr;
Db *partLib = nullptr;

json previewPart = json::object();
json currentPart = json::object();
QString previewPartMD5;
QString currentPartMD5;

QList<QUndoCommand *> preChildCommands;
QList<QUndoCommand *> postChildCommands;
QVector<WireSegmentItem *> mergeQueue;


/**
 * ***********************************************************************
 *
 *  持久化全局变量
 *
 * ***********************************************************************
 */

QString defaultPageSize = "A4";
int designGridSize = 10;
int displayGridSize = 10;
QString currentColorScheme = "orcad";


// 依靠页面名称单独保存原理图页 不能靠数组索引（删除页面后索引改变）
QHash<QString,SchematicScene *> schPages;

json schematic = json::parse(defaultSchematic);

// 目前禁止自定义管脚、电源、分页符 如果规范不一致使用编辑器库
// 库数据保存在原理图中方便其它工具解析从而不依赖编辑器
json &schProperty = schematic["schProperty"];
json &schPinLib = schematic["schPinLib"];
json &schPowerLib = schematic["schPowerLib"];
json &schOffpageLib = schematic["schOffpageLib"];

json &schPartLib = schematic["schPartLib"];
json &pages = schematic["pages"];
// 设置
json globalSetting = json::object();
json colorSchemes = json::object();

QHash<QString,int> partPrefixMaxIndex;
QMultiHash<QString,int> partPrefixIndex;
QMultiHash<QString,PartItem*> partTypePart;

int netNameMaxIndex = 100000;
QMultiHash<QString,PortItem*> schNets;


// Junction @J
int junctionMaxIndex = 0;
// 电源 @P
int powerMaxIndex = 0;
// 地 @G
int gndMaxIndex = 0;

/**
 * ***********************************************************************
 *
 *  标识符重载
 *
 * ***********************************************************************
 */


/**
 * ***********************************************************************
 *
 *  全局函数
 *
 * ***********************************************************************
 */

void from_json(const json& j,colorScheme& color) {
    color.background = QString::fromStdString(j["background"].get<std::string>());
    color.display = QString::fromStdString(j["display"].get<std::string>());
    color.selection = QString::fromStdString(j["selection"].get<std::string>());
    color.drawing = QString::fromStdString(j["drawing"].get<std::string>());
}


const QPointF flagToPoint(int flag,const QRectF &rect)
{
    switch (flag) {
        case 0:
            return rect.topLeft();
        case 1:
            return rect.topRight();
        case 2:
            return rect.bottomRight();
        case 3:
            return rect.bottomLeft();
    }
    return QPointF();
}

float cartesian2degree(qreal x, qreal y)
{
    float degree;
    if (x > 0 && y <= 0)
    {
        degree = qRadiansToDegrees(qAtan(-y / x));
    }
    else if (x < 0)
    {
        degree = qRadiansToDegrees(qAtan(-y / x) + M_PI);
    }
    else if (x == 0 && y < 0)
    {
        degree = 90;
    }
    else if (x == 0 && y > 0)
    {
        degree = 270;
    }
    else if (x > 0 && y > 0)
    {
        // 无法画圆
        degree = qRadiansToDegrees(qAtan(-y / x) + 2 * M_PI);
    }
    return degree;
}

const QString makeNetName()
{
    netNameMaxIndex += 1;
    QString newNet = QString("N%1").arg(netNameMaxIndex);
    if(schNets.contains(newNet)){
        return makeNetName();
    }else{
        return newNet;
    }
}
