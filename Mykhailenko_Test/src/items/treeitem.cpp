#include "treeitem.h"

TreeItem::TreeItem(const QString &data, TreeItem *parent)
    : m_itemData(data), m_parentItem(parent) {}

TreeItem::~TreeItem() {

}

void TreeItem::appendChild(std::unique_ptr<TreeItem> child) {
    m_childItems.push_back(std::move(child));
}

TreeItem *TreeItem::child(int row) {
    return m_childItems[row].get();
}

size_t TreeItem::childCount() const {
    return m_childItems.size();
}

size_t TreeItem::row() const {
    if (m_parentItem) {
        for (size_t i = 0; i < m_parentItem->m_childItems.size(); ++i) {
            if (m_parentItem->m_childItems[i].get() == this) {
                return i;
            }
        }
    }
    return 0;
}

TreeItem *TreeItem::parentItem() {
    return m_parentItem;
}

QVariant TreeItem::data(int role) const {
    if (role == Qt::DisplayRole) {
        return m_itemData;
    }
    return QVariant();
}
