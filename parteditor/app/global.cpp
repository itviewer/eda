#include "global.h"
#include <QtMath>

/**
 * ***********************************************************************
 *
 *  非持久化全局变量
 *
 * ***********************************************************************
 */
bool snapToGrid = true;
colorScheme schColor;

PartEditor *partEditor = nullptr;
StateMachine *fsm = nullptr;
Db *partLib = nullptr;

QVector<PartScene *> partScenes;
PackageScene *packageScene = nullptr;


QString partName = "";
QString partPrefix = "";
QString footprint = "";
int partPackageType = 0;
int partNumbers = 3;
int partNumbering = 0;
int partLibId = 0;

int currentPartNumber = 0;

/**
 * ***********************************************************************
 *
 *  持久化全局变量
 *
 * ***********************************************************************
 */

int designGridSize = 10;
int displayGridSize = 10;


/**
 * ***********************************************************************
 *
 *  全局函数
 *
 * ***********************************************************************
 */

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
