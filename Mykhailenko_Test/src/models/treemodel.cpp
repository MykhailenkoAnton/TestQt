#include "treemodel.h"

#include <QDebug>

#include "countryitem.h"
#include "operatoritem.h"

TreeModel::TreeModel(std::unique_ptr<Storage> storage, QObject *parent)
    : QAbstractItemModel(parent), m_storage(std::move(storage)) {
    m_rootItem = std::make_unique<TreeItem>("");
    setupModelData();
}

TreeModel::~TreeModel() {
}

void TreeModel::setupModelData() {
    QList<QVariant> countries = m_storage->load("Country");
    qDebug() << "Loaded countries: " << countries.size();
    for (const auto &variant : countries) {
        Country country = variant.value<Country>();
        if (!countryItems.contains(country.code)) {
            auto countryItem = std::make_unique<CountryItem>(country, m_rootItem.get());
            countryItems[country.code] = countryItem.get();
            m_rootItem->appendChild(std::move(countryItem));
        }
    }

    QList<QVariant> operators = m_storage->load("Operator");
    qDebug() << "Loaded operators: " << operators.size();
    for (const auto &variant : operators) {
        Operator op = variant.value<Operator>();
        QString countryCode;
        for (const auto &variant : countries) {
            Country country = variant.value<Country>();
            if (country.mcc == op.mcc) {
                countryCode = country.code;
                break;
            }
        }
        if (countryItems.contains(countryCode)) {
            auto operatorItem = std::make_unique<OperatorItem>(op, countryItems[countryCode]);
            countryItems[countryCode]->appendChild(std::move(operatorItem));
        }
    }

    qDebug() << "Model setup complete. Countries loaded:" << countries.size() << "Operators loaded:" << operators.size();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    return item->data(role);
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;
    return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return "Countries and Operators";
    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = m_rootItem.get();
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const {
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == m_rootItem.get())
        return QModelIndex();

    return createIndex(static_cast<int>(parentItem->row()), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const {
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = m_rootItem.get();
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return static_cast<int>(parentItem->childCount());
}

int TreeModel::columnCount(const QModelIndex &parent) const {
    return 1;
}
