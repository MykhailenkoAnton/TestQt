#include "countryitem.h"

#include <QFile>
#include <QIcon>
#include <QVariant>
#include <QDebug>

CountryItem::CountryItem(const Country &country, TreeItem *parent)
    : TreeItem(country.name, parent), m_country(country) {
}

QVariant CountryItem::data(int role) const {
    if (role == Qt::DisplayRole) {
        return QString("%1 (%2)").arg(m_country.name).arg(m_country.code);
    }
    if (role == Qt::UserRole + 4) {
        return m_country.code;
    }
    return QVariant();
}
