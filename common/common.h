#ifndef COMMON_H
#define COMMON_H

#include <QDebug>
#include "jsontype.h"

/**
 * ***********************************************************************
 *
 * 全局常量
 *
 * ***********************************************************************
 */

const qreal schSpecVersion = 1.0;
const qreal pcbSpecVersion = 1.0;
const qreal partLibSpecVersion = 1.0;
const qreal footprintLibSpecVersion = 1.0;

const qreal inchPerUnit = 0.01;
const qreal milPerUnit = 10.0;
const qreal mmPerUnit = 0.254;

const QSizeF ISOA0 = QSizeF(4681.10,3311.02);
const QSizeF ISOA1 = QSizeF(3311.02,2338.58);
const QSizeF ISOA2 = QSizeF(2338.58,1653.54);
const QSizeF ISOA3 = QSizeF(1653.54,1169.29);
const QSizeF ISOA4 = QSizeF(1169.29,826.77);

const QSizeF ANSIA = QSizeF(1100,850);
const QSizeF ANSIB = QSizeF(1700,1100);
const QSizeF ANSIC = QSizeF(2200,1700);
const QSizeF ANSID = QSizeF(3400,2200);
const QSizeF ANSIE = QSizeF(4400,3400);

const QHash<QString,QSizeF> pageSizeOption =
{
    {"A0",ISOA0},
    {"A1",ISOA1},
    {"A2",ISOA2},
    {"A3",ISOA3},
    {"A4",ISOA4},
    {"A",ANSIA},
    {"B",ANSIB},
    {"C",ANSIC},
    {"D",ANSID},
    {"E",ANSIE}
};

const QVector<QString> alphabet =
{
    "A","B","C","D","E","F","G","H","I","J","K","L","M",
    "N","O","P","Q","R","S","T","U","V","W","X","Y","Z"
};

const QVector<QString> partPrefixList
{
    "U","R","C"
};

const QHash<QString,QString> partPrefixMap
{
    {"U","IC(U)"},
    {"R","电阻(R)"},
    {"C","电容(C)"}
};

const QString DS = "/";
/**
 * ***********************************************************************
 *
 * 数据结构定义和声明
 *
 * ***********************************************************************
 */

enum JsonFormat
{
    Binary,
    Json
};

enum Units
{
    mil,
    mm,
    inch
};

/**
 * ***********************************************************************
 *
 * 非持久化全局变量
 *
 * ***********************************************************************
 */
extern QString settingDir;

/**
 * ***********************************************************************
 *
 *  标识符重载
 *
 * ***********************************************************************
 */
QDebug operator<<(QDebug out, const json& js);

/**
 * ***********************************************************************
 *
 * 全局函数
 *
 * ***********************************************************************
 */

// 非阻塞延迟
extern void sleep(int milliseconds,int step = 100);

extern Qt::ToolBarArea dockAreaToToolBarArea(Qt::DockWidgetArea area);
extern Qt::Orientation areaToOrientation(Qt::DockWidgetArea area);

extern bool loadJsonDocument(const QString& filename, json& j, const JsonFormat& format = JsonFormat::Json);
extern bool saveJsonDocument(const QString& filename, const json& j, const JsonFormat& format = JsonFormat::Json);

extern QString md5(const QString &str,const QString &salt = "",bool middle = true);
extern int random(int min = 1025,int max = 65534);

extern const QPointF gridPoint(QPointF point,const int gridSize);
#endif // COMMON_H
