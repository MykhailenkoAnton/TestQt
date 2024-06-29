#ifndef STORAGE_H
#define STORAGE_H

#include <QList>
#include <QVariant>

class Storage {
public:
    virtual ~Storage() = default;
    virtual QList<QVariant> load(const QString &type) = 0;
};

#endif // STORAGE_H
