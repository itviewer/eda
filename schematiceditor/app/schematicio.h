#ifndef SCHEMATICIO_H
#define SCHEMATICIO_H

#include <QObject>
#include "global.h"

class SchematicIO : public QObject
{
    Q_OBJECT
public:
    explicit SchematicIO(QObject *parent = nullptr);

    bool loadSchematic(const QString &filename,json &j, const JsonFormat &format = JsonFormat::Json) const;
    bool saveSchematic(const JsonFormat &format = JsonFormat::Json) const;

signals:

public slots:
private:
};

#endif // SCHEMATICIO_H
