#ifndef JSONTYPE_H
#define JSONTYPE_H

#include <QString>
#include <QPointF>
#include <QRectF>
#include <QLineF>
#include <QPolygonF>
#include <QSizeF>
#include <QVariant>

#include "json.hpp"
using json = nlohmann::json;

extern void to_json(json& j, const QPointF& p);
extern void to_json(json& j, const QPoint& p);
extern void to_json(json& j, const QRectF& rect);
extern void to_json(json& j, const QLineF& line);
extern void to_json(json& j, const QString& str);
extern void to_json(json& j, const QSizeF& size);
extern void to_json(json& j, const QPolygonF& polygon);

extern void from_json(const json& j, QPointF& p);
extern void from_json(const json& j, QRectF& rect);
extern void from_json(const json& j, QLineF& line);
extern void from_json(const json& j, QString& str);
extern void from_json(const json& j, QSizeF& size);
extern void from_json(const json& j, QPolygonF& polygon);
extern void from_json(const json& j, QVariant& var);

#endif // JSONTYPE_H
