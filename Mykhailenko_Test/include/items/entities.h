#ifndef ENTITIES_H
#define ENTITIES_H

#include <QString>
#include <QMetaType>

struct Country {
    int mcc;
    QString code;
    QString name;
    int mncLength;
};

struct Operator {
    int mcc;
    int mnc;
    QString name;
};

Q_DECLARE_METATYPE(Country)
Q_DECLARE_METATYPE(Operator)

#endif // ENTITIES_H
