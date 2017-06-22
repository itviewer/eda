#include "db.h"
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QVariant>

Db::Db(const QString &database, const QString &connectionName)
{
    if(QSqlDatabase::contains(connectionName)){
        db = QSqlDatabase::database(connectionName);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",connectionName);
    }
    db.setDatabaseName(database);
    if(!db.isOpen() && !db.open()){
        QMessageBox::critical(0,("Cannot open database"),
            ("Unable to establish a database connection.\n"), QMessageBox::Cancel);
    }
    db.exec("PRAGMA foreign_keys = ON");
    query = QSqlQuery(db);
}

Db::~Db()
{
}

QSqlDatabase &Db::database()
{
    return db;
}

int Db::load(const QString &database)
{
    return db.load(database);
}

int Db::dump(const QString &database)
{
    return db.dump(database);
}

int Db::insert(const QString &sql, const QVariantList &bindValue)
{
    int row = 0;
    if(exec(sql,bindValue)){
        row = query.lastInsertId().toInt();
    }
    return row;
}

bool Db::remove(const QString &sql, const QVariantList &bindValue)
{
    return exec(sql,bindValue);
}

bool Db::update(const QString &sql, const QVariantList &bindValue)
{
    return exec(sql,bindValue);
}

const QVariantHash Db::get(const QString &sql, const QVariantList &bindValue)
{
    QVariantHash row;
    query.prepare(sql);
    if(!bindValue.isEmpty()){
        for(auto &v:bindValue){
            query.addBindValue(v);
        }
    }

    if(query.exec() && query.last()){
        QSqlRecord data = query.record();
        QSqlField field;
        int cols = data.count();
        for(int i = 0;i < cols; i++){
            field = data.field(i);
            row.insert(field.name(),field.value());
        }
    }
    return row;
}

const QVector<QVariantHash> Db::select(const QString &sql, const QVariantList &bindValue)
{
    QVector<QVariantHash> result;
    query.prepare(sql);
    if(!bindValue.isEmpty()){
        for(auto &v:bindValue){
            query.addBindValue(v);
        }
    }

    if(query.exec()){
        QSqlRecord data;
        QSqlField field;
        while (query.next()) {
            QVariantHash row;
            data = query.record();
            int cols = data.count();
            for(int i = 0;i < cols; i++){
                field = data.field(i);
                row.insert(field.name(),field.value());
            }
            result.append(row);
        }
    }
    return result;
}

QSqlError Db::dbError() const
{
    return db.lastError();
}

QSqlError Db::queryError() const
{
    return query.lastError();
}

inline bool Db::exec(const QString &sql, const QVariantList &bindValue)
{
    query.prepare(sql);
    if(!bindValue.isEmpty()){
        for(auto &v:bindValue){
            query.addBindValue(v);
        }
    }
    return query.exec();
}
