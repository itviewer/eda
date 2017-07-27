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
    j.push_back(p.x());
    j.push_back(p.y());
}

void to_json(json& j, const QPoint& p)
{
    j.push_back(p.x());
    j.push_back(p.y());
}

void to_json(json& j, const QRectF& rect)
{
    j.push_back(rect.x());
    j.push_back(rect.y());
    j.push_back(rect.width());
    j.push_back(rect.height());
}

void to_json(json& j, const QLineF& line)
{
    j.push_back(line.p1());
    j.push_back(line.p2());
}

void to_json(json& j, const QString& str)
{
    j = str.toStdString();
}

void to_json(json &j, const QSizeF &size)
{
    j.push_back(size.width());
    j.push_back(size.height());
}

void to_json(json& j, const QPolygonF& polygon)
{
    for(QPolygonF::const_reference it:polygon){
        j.push_back(it);
    }
}

void to_json(json& j, const QVector<QString>& vector)
{
    int i = 0;
    for(const QString &item:vector){
        j[i] = item.toStdString();
        i++;
    }
}

void to_json(json& j, const QHash<QString,QString>& hash)
{
    for(auto it = hash.cbegin();it != hash.cend();it++){
        j[it.key().toStdString()] = it.value().toStdString();
    }
}

void from_json(const json& j, QPointF& p)
{
    p.setX(j.at(0).get<double>());
    p.setY(j.at(1).get<double>());
}

void from_json(const json& j, QRectF& rect)
{
    rect.setX(j.at(0).get<double>());
    rect.setY(j.at(1).get<double>());
    rect.setWidth(j.at(2).get<double>());
    rect.setHeight(j.at(3).get<double>());
}

void from_json(const json& j, QLineF& line)
{
    line.setP1(j.at(0));
    line.setP2(j.at(1));
}

void from_json(const json& j, QString& str)
{
    str = QString::fromStdString(j.get<std::string>());
}

void from_json(const json &j, QSizeF &size)
{
    size.setWidth(j.at(0).get<double>());
    size.setHeight(j.at(1).get<double>());
}

void from_json(const json& j, QPolygonF& polygon)
{
    for(auto &i:j){
        polygon << i.get<QPointF>();
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

void from_json(const json& j,QVector<QString>& vector)
{
    vector.clear();
    for (auto& item : j) {
      vector.append(item);
    }
}

void from_json(const json& j, QHash<QString, QString> &hash) {
    hash.clear();
    for(auto it = j.begin();it != j.end();it++){
        hash.insert(QString::fromStdString(it.key()),QString::fromStdString(it.value()));
    }
}
