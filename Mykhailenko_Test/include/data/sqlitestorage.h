#ifndef SQLITESTORAGE_H
#define SQLITESTORAGE_H

#include "storage.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

class SQLiteStorage : public Storage {
public:
    explicit SQLiteStorage(const QString &dbName);
    ~SQLiteStorage();

    QList<QVariant> load(const QString &type) override;

private:
    QSqlDatabase m_db;
};

#endif // SQLITESTORAGE_H
