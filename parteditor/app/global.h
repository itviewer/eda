#ifndef GLOBAL_H
#define GLOBAL_H

#include "common.h"

class StateMachine;
class PartEditor;
class PartScene;
class PackageScene;
class Db;

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

    PackageItemType = 200000,
    PinItemType = 200001
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

    PinItemState
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
    SuperThick = 6
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

enum PackageType
{
    Heterogenous,
    Homogeneous
};

enum Numbering
{
    Alphabetic,
    Numeric
};

/**
 * ***********************************************************************
 *
 * 全局常量
 *
 * ***********************************************************************
 */
const int maxSceneWidth = 5000;
const int maxSceneHeight = 5000;

/**
 * ***********************************************************************
 *
 * 非持久化全局变量
 *
 * ***********************************************************************
 */
extern bool snapToGrid;
extern colorScheme schColor;

extern PartEditor *partEditor;
extern StateMachine *fsm;
extern Db *partLib;

extern QVector<PartScene *> partScenes;
extern PackageScene *packageScene;

// 元件基本信息
extern QString partName;
extern QString partPrefix;
extern QString footprint;
extern int partPackageType;
extern int partNumbers;
extern int partNumbering;
extern int partLibId;

extern int currentPartNumber;

/**
 * ***********************************************************************
 *
 * 持久化全局变量
 *
 * ***********************************************************************
 */
extern int designGridSize;
extern int displayGridSize;

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
extern const QPointF flagToPoint(int flag,const QRectF &rect);

extern float cartesian2degree(qreal x, qreal y);
#endif // GLOBAL_H
