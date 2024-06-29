#include "sqlitestorage.h"

#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

#include "entities.h"

SQLiteStorage::SQLiteStorage(const QString &dbName) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbName);
    if (!m_db.open()) {
        qWarning() << "Failed to open database:" << m_db.lastError().text();
    } else {
        qDebug() << "Database opened successfully.";
    }
}

SQLiteStorage::~SQLiteStorage() {
    m_db.close();
}

QList<QVariant> SQLiteStorage::load(const QString &type) {
    QList<QVariant> list;

    if (type == "Country") {
        QSqlQuery query("SELECT mcc, code, name, mnc_length FROM countries");
        if (!query.exec()) {
            qWarning() << "Failed to execute query for countries:" << query.lastError().text();
        } else {
            while (query.next()) {
                Country country;
                country.mcc = query.value(0).toInt();
                country.code = query.value(1).toString();
                country.name = query.value(2).toString();
                country.mncLength = query.value(3).toInt();
                list.append(QVariant::fromValue(country));
                qDebug() << "Loaded country:" << country.code << country.name;
            }
        }
    } else if (type == "Operator") {
        QSqlQuery query("SELECT name, mcc, mnc FROM operators");
        if (!query.exec()) {
            qWarning() << "Failed to execute query for operators:" << query.lastError().text();
        } else {
            while (query.next()) {
                Operator op;
                op.name = query.value(0).toString();
                op.mcc = query.value(1).toInt();
                op.mnc = query.value(2).toInt();
                list.append(QVariant::fromValue(op));
                qDebug() << "Loaded operator:" << op.name << op.mcc << op.mnc;
            }
        }
    }

    return list;
}
