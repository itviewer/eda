#ifndef GLOBAL_H
#define GLOBAL_H

#include <QDebug>

#include "common.h"

class PCBScene;
class PCBEditor;
class FootprintEditor;
class StateMachine;
class QGraphicsItem;

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

    // 基本电气图形
    ApertureItemType = 200000,
    PadItemType = 200001,
    ViaItemType = 200002,
    TraceLineItemType = 200003,
    TraceArcItemType = 200004,

    // 组合图形
    PackageItemType = 300000,
    FootprintItemType = 300001,
    TraceItemType = 300002,
    OutlineItemType = 300003
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

    ViaItemState,
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

// QFlags 还不支持64位
// 这里直接使用 非 类型安全的数值类型，好处是不需要在Qt框架内定义数据结构
enum Layer : quint64
{
    TopLayer = 0x1,
    BottomLayer = 0x2,
    TopSilkLayer = 0x4,
    BottomSilkLayer = 0x8,//layer 4
    TopPasteLayer = 0x10,
    BottomPasteLayer = 0x20,
    TopSolderLayer = 0x40,
    BottomSolderLayer = 0x80,//layer 8
    TopAssemblyLayer = 0x100,
    BottomAssemblyLayer = 0x200,
    BoardOutlineLayer = 0x400,
    KeepOutLayer = 0x800,//layer 12

    Reserved1Layer = 0x1000,
    Reserved2Layer = 0x2000,
    Reserved3Layer = 0x4000,
    Reserved4Layer = 0x8000,//layer 16
    Reserved5Layer = 0x10000,
    Reserved6Layer = 0x20000,
    Reserved7Layer = 0x40000,
    Reserved8Layer = 0x80000,//layer 20

    Custom1Layer = 0x100000,
    Custom2Layer = 0x200000,
    Custom3Layer = 0x400000,
    Custom4Layer = 0x800000,//layer 24
    Custom5Layer = 0x1000000,
    Custom6Layer = 0x2000000,
    Custom7Layer = 0x4000000,
    Custom8Layer = 0x8000000,//layer 28
    Custom9Layer = 0x10000000,
    Custom10Layer = 0x20000000,
    Custom11Layer = 0x40000000,
    Custom12Layer = 0x80000000,//layer 32
    Custom13Layer = 0x100000000,
    Custom14Layer = 0x200000000,
    Custom15Layer = 0x400000000,
    Custom16Layer = 0x800000000,//layer 36
    Custom17Layer = 0x1000000000,
    Custom18Layer = 0x2000000000,
    Custom19Layer = 0x4000000000,
    Custom20Layer = 0x8000000000,//layer 40
    Custom21Layer = 0x10000000000,
    Custom22Layer = 0x20000000000,
    Custom23Layer = 0x40000000000,
    Custom24Layer = 0x80000000000,//layer 44
    Custom25Layer = 0x100000000000,
    Custom26Layer = 0x200000000000,
    Custom27Layer = 0x400000000000,
    Custom28Layer = 0x800000000000,//layer 48
    Custom29Layer = 0x1000000000000,
    Custom30Layer = 0x2000000000000,
    Custom31Layer = 0x4000000000000,
    Custom32Layer = 0x8000000000000,//layer 52
    Custom33Layer = 0x10000000000000,
    Custom34Layer = 0x20000000000000,
    Custom35Layer = 0x40000000000000,
    Custom36Layer = 0x80000000000000,//layer 56
    Custom37Layer = 0x100000000000000,
    Custom38Layer = 0x200000000000000,
    Custom39Layer = 0x400000000000000,
    Custom40Layer = 0x800000000000000,//layer 60
    Custom41Layer = 0x1000000000000000,
    Custom42Layer = 0x2000000000000000,
    Custom43Layer = 0x4000000000000000,
    Custom44Layer = 0x8000000000000000, //layer 64

    AllLayer = 0xffffffffffffffff
};

enum Aperture
{
    CircleAperture,
    RectangleAperture,
    ObroundAperture,
    PolygonAperture     // 正多边形
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
extern FootprintEditor *footprintEditor;
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

extern QMap<Layer,QHash<QString,QVariant>> layerProperty;
extern QHash<Layer,QHash<QString,QString>> layerColors;
extern QHash<Layer,QSet<QGraphicsItem *>> layerItems;


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
