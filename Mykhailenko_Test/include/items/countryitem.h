#ifndef COUNTRYITEM_H
#define COUNTRYITEM_H

#include "treeitem.h"
#include "entities.h"

class CountryItem : public TreeItem {
public:
    explicit CountryItem(const Country &country, TreeItem *parent = nullptr);
    QVariant data(int role) const override;

    QString code() const { return m_country.code; }
    QString name() const { return m_country.name; }

private:
    Country m_country;
};

#endif // COUNTRYITEM_H
