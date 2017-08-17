#include "global.h"
#include <QtMath>

/**
 * ***********************************************************************
 *
 * 非持久化全局变量
 *
 * ***********************************************************************
 */

bool snapToGrid = true;
colorScheme schColor;

PCBEditor *pcbEditor = nullptr;
FootprintEditor *footprintEditor = nullptr;
StateMachine *fsm = nullptr;

/**
 * ***********************************************************************
 *
 * 持久化全局变量
 *
 * ***********************************************************************
 */
int designGridSize = 10;
int displayGridSize = 10;


// 设置
json globalSetting = json::object();
json colorSchemes = json::object();

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
