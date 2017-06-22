#ifndef DB_H
#define DB_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>

class Db
{

public:
    explicit Db(const QString &database,const QString &connectionName = QLatin1String("qt_sql_default_connection"));
    ~Db();

    QSqlDatabase &database();
    int load(const QString &database);
    int dump(const QString &database);

    int insert(const QString &sql,const QVariantList &bindValue = {});
    bool remove(const QString &sql,const QVariantList &bindValue = {});
    bool update(const QString &sql,const QVariantList &bindValue = {});

    const QVariantHash get(const QString &sql,const QVariantList &bindValue = {});
    const QVector<QVariantHash> select(const QString &sql,const QVariantList &bindValue = {});

    QSqlError dbError() const;
    QSqlError queryError() const;

private:
    QSqlDatabase db;
    QSqlQuery query;

    inline bool exec(const QString &sql,const QVariantList &bindValue = {});
};

#endif // DB_H
