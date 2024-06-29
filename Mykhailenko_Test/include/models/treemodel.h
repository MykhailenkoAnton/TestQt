#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <memory>
#include <QMap>

#include "storage.h"
#include "treeitem.h"
#include "countryitem.h"
#include "operatoritem.h"

class TreeModel : public QAbstractItemModel {
    Q_OBJECT

public:
    explicit TreeModel(std::unique_ptr<Storage> storage, QObject *parent = nullptr);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
    void setupModelData();
    std::unique_ptr<TreeItem> m_rootItem;
    std::unique_ptr<Storage> m_storage;
    QMap<QString, CountryItem*> countryItems;
};

#endif // TREEMODEL_H
