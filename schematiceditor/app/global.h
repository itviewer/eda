#ifndef GLOBAL_H
#define GLOBAL_H

#include "common.h"

class PartItem;
class PortItem;
class SchematicScene;
class SchematicEditor;
class PartEditor;
class StateMachine;
class Db;
class QUndoCommand;
class WireSegmentItem;
class SchematicIO;
class SettingIO;

/**
 * ***********************************************************************
 *
 * 数据结构定义和声明
 *
 * ***********************************************************************
 */

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
    NodeItemType = 200000,
    NoConnectItemType = 200001,
    PortItemType = 200002,
    JunctionItemType = 200003,
    WireSegmentItemType = 200004,

    // 组合图形
    PackageItemType = 300000,
    PageBorderItemType = 300001,
    TitleBlockItemType = 300002,
    PinItemType = 300003,
    PartItemType = 300004,
    PowerItemType = 300005,
    GndItemType = 300006,
    BusItemType = 300007,
    BusEntryItemType = 300008,
    OffpageItemType = 300009,

    PartPreviewItemType = 400000
};

enum ZValue
{
    BaseItemZValue = 1,

    WireSegmentItemZValue = 2,
    SelectedWireSegmentItemZValue = 3,
    PortItemZValue = 4,
    JunctionItemZValue = 5,

    PinItemZValue = 6,//??
    PartItemZValue = 7,
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

    WireSegmentItemState,
    JunctionItemState,
    PinItemState,
    PartItemState,

    NoConnectItemState,
    PowerItemState,
    GndItemState,
    BusItemState,
    BusEntryItemState,
    OffpageItemState,
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

enum TreeItem{
    SchematicNavigatorItem = 1001,
    PartTypeNavigatorItem = 1002,
    PartNavigatorItem = 1003,
    NetNavigatorItem = 1004,

    SchTreeItem = 2001,
    PartTypeTreeItem = 2002,
    PartTreeItem = 2003,
    NetTreeItem = 2004
};

enum PortState{
    FloatingPort,
    NoConnectPort,
    ConnectedPort
};

enum PinShape
{
    LineShape,
    ShortShape,
    ClockShape,
    DotShape,
    DotClockShape,
    ShortClockShape,
    ShortDotShape,
    ShortDotClockShape,
};

enum PinType
{
    InputType,
    OutputType,
    PassiveType
};

enum Command
{
    ItemUndoCommandType,
    WireUndoCommandType
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
 * 全局常量
 *
 * ***********************************************************************
 */
const int maxPageWidth = 5000;
const int maxPageHeight = 5000;
const QString schSettingFileName = "schsetting.json";

/**
 * ***********************************************************************
 *
 * 非持久化全局变量
 *
 * ***********************************************************************
 */

extern bool snapToGrid;
extern QHash<QString,QString> schColor;
extern QVector<QString> schColorScheme;

extern SchematicEditor *schEditor;
extern PartEditor *partEditor;
extern SchematicIO *schIO;
extern SettingIO *settingIO;
extern StateMachine *fsm;
extern Db *partLib;

extern json previewPart;
extern json currentPart;
extern QString previewPartMD5;
extern QString currentPartMD5;

extern QList<QUndoCommand *> preChildCommands;
extern QList<QUndoCommand *> postChildCommands;
extern QVector<WireSegmentItem *> mergeQueue;

/**
 * ***********************************************************************
 *
 * 持久化全局变量
 *
 * ***********************************************************************
 */

extern QString defaultPageSize;
extern int designGridSize;
extern int displayGridSize;
extern QString currentColorScheme;

// 设置
extern json schSetting;
extern json &schSettingGeneral;
extern json &schGlobalSettingGeneral;
extern json &schGlobalSettingDesign;
extern json &schGlobalSettingText;
extern json &schGlobalSettingLineWidth;
extern json &schGlobalSettingColorScheme;

// 按字符串排序没有意义
extern QHash<QString,SchematicScene *> schPages;

extern json schematic;
// 目前禁止自定义管脚、电源、分页符 如果规范一致则使用原理图中数据即可 否则使用编辑器库
// 索引真的有用？
extern json &schProperty;
extern json &schPinLib;
extern json &schPowerLib;
extern json &schOffpageLib;
extern json &schPartLib;
extern json &pages;

// 元件
// 前缀及其最大索引
extern QHash<QString,int> partPrefixMaxIndex;
// 前缀及其所有索引
extern QMultiHash<QString,int> partPrefixIndex;
// 元件类型及其所有元件
extern QMultiHash<QString,PartItem*> partTypePart;


// 当前自动生成网络名最大索引
extern int netNameMaxIndex;
// 所有网络及连接的端点
extern QMultiHash<QString,PortItem*> schNets;

// Junction @J
extern int junctionMaxIndex;
// 电源 @P
extern int powerMaxIndex;
// 地 @G
extern int gndMaxIndex;

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

extern const QString makeNetName();
#endif // GLOBAL_H
