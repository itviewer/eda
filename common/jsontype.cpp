#include "jsontype.h"
#include <QDebug>
/**
 * ***********************************************************************
 *
 * 这里不做类型验证 如果试图转换的数据不满足类型要求程序可能崩溃
 *
 * ***********************************************************************
 */

void to_json(json& j, const QPointF& p)
{
    j = json{p.x(), p.y()};
}

void to_json(json& j, const QPoint& p)
{
    j = json{p.x(), p.y()};
}

void to_json(json& j, const QRectF& rect)
{
    j = json{rect.x(), rect.y(), rect.width(), rect.height()};
}

void to_json(json& j, const QLineF& line)
{
    j = json{line.p1(), line.p2()};
}

void to_json(json& j, const QString& str)
{
    j = str.toStdString();
}

void to_json(json &j, const QSizeF &size)
{
    j = json{size.width(),size.height()};
}

void to_json(json& j, const QPolygonF& polygon)
{
    for(QPolygonF::const_reference it:polygon){
        j.push_back(it);
    }
}

void from_json(const json& j, QPointF& p)
{
    p.setX(j[0].get<double>());
    p.setY(j[1].get<double>());
}

void from_json(const json& j, QRectF& rect)
{
    rect.setX(j[0].get<double>());
    rect.setY(j[1].get<double>());
    rect.setWidth(j[2].get<double>());
    rect.setHeight(j[3].get<double>());
}

void from_json(const json& j, QLineF& line)
{
    line.setP1(j[0]);
    line.setP2(j[1]);
}

void from_json(const json& j, QString& str)
{
    str = QString::fromStdString(j.get<std::string>());
}

void from_json(const json &j, QSizeF &size)
{
    size.setWidth(j[0].get<double>());
    size.setHeight(j[1].get<double>());
}

void from_json(const json& j, QPolygonF& polygon)
{
    for(auto &i:j){
        polygon << QPointF(i);
    }
}

void from_json(const json& j, QVariant& var)
{
    if(j.is_string()){
        var = QString::fromStdString(j.get<std::string>());
    }else if(j.is_number_float()){
        var = j.get<double>();
    }else if(j.is_number_integer()){
        var = j.get<int>();
    }else if(j.is_boolean()){
        var = j.get<bool>();
    }
}
