#ifndef GLOBAL_H
#define GLOBAL_H

#include <QDebug>

#include "common.h"

class PCBScene;
class PCBEditor;
class StateMachine;

/**
 * ***********************************************************************
 *
 * 数据结构定义和声明
 *
 * ***********************************************************************
 */

struct colorScheme
{
    QString background;
    QString display;
    QString selection;
    QString drawing;
};

enum Item
{
    // 基本2D Line
    LineItemType = 100001,
    PolylineItemType = 100002,
    RectItemType = 100003,
    RoundedRectItemType = 100004,
    EllipseItemType = 100005,
    PolygonItemType = 100006,
    ArcItemType = 100007,
    CubicBezierItemType = 100008,
    TextItemType = 100009,
    PixmapItemType = 100010,

    // 组合图形
    PackageItemType = 300000
};

enum FSM
{
    SelectState,
    LineItemState,
    PolylineItemState,
    RectItemState,
    RoundedRectItemState,
    EllipseItemState,
    PolygonItemState,
    ArcItemState,
    CubicBezierItemState,
    TextItemState,
    PixmapItemState,

    PadItemState,
    TraceItemState
};

enum ZValue
{
    BaseItemZValue = 1
};

enum LineStyle{
    NoPen = Qt::NoPen,
    SolidLine = Qt::SolidLine,
    DashLine = Qt::DashLine,
    DotLine = Qt::DotLine,
    DashDotLine = Qt::DashDotLine,
    DashDotDotLine = Qt::DashDotDotLine
};

enum LineWidth{
    Normal = 0,
    Thick = 3,
    SuperThick = 5
};

enum FillStyle{
    NoBrush = Qt::NoBrush,
    SolidPattern = Qt::SolidPattern,
    HorPattern = Qt::HorPattern,
    VerPattern = Qt::VerPattern,
    CrossPattern = Qt::CrossPattern,
    BDiagPattern = Qt::BDiagPattern,
    FDiagPattern = Qt::FDiagPattern,
    DiagCrossPattern = Qt::DiagCrossPattern,
};

enum Angle
{
    Diagonal,
    Orthogonal,
    AnyAngle
};

/**
 * ***********************************************************************
 *
 * 非持久化全局变量
 *
 * ***********************************************************************
 */

extern bool snapToGrid;
extern colorScheme schColor;

extern PCBEditor *pcbEditor;
extern StateMachine *fsm;

/**
 * ***********************************************************************
 *
 * 持久化全局变量
 *
 * ***********************************************************************
 */
extern int designGridSize;
extern int displayGridSize;


// 设置
extern json globalSetting;
extern json colorSchemes;
/**
 * ***********************************************************************
 *
 * 标识符重载
 *
 * ***********************************************************************
 */

/**
 * ***********************************************************************
 *
 * 全局函数
 *
 * ***********************************************************************
 */
extern void from_json(const json& j,colorScheme& color);

extern const QPointF flagToPoint(int flag,const QRectF &rect);

extern float cartesian2degree(qreal x, qreal y);

#endif // GLOBAL_H
