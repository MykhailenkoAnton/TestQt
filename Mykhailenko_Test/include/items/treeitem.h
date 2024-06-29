#ifndef TREEITEM_H
#define TREEITEM_H

#include <vector>
#include <QVariant>
#include <QString>
#include <memory>

class TreeItem {
public:
    explicit TreeItem(const QString &data, TreeItem *parentItem = nullptr);
    virtual ~TreeItem();

    void appendChild(std::unique_ptr<TreeItem> child);
    TreeItem *child(int row);
    size_t childCount() const;
    size_t row() const;
    TreeItem *parentItem();
    virtual QVariant data(int role) const;

protected:
    std::vector<std::unique_ptr<TreeItem>> m_childItems;
    QString m_itemData;
    TreeItem *m_parentItem;
};

#endif // TREEITEM_H
