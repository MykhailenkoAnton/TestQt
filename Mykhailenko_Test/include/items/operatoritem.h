#ifndef OPERATORITEM_H
#define OPERATORITEM_H

#include "treeitem.h"
#include "entities.h"

class OperatorItem : public TreeItem {
public:
    explicit OperatorItem(const Operator &op, TreeItem *parent = nullptr);
    QVariant data(int role) const override;

    int mcc() const { return m_operator.mcc; }
    int mnc() const { return m_operator.mnc; }
    QString name() const { return m_operator.name; }

private:
    Operator m_operator;
};

#endif // OPERATORITEM_H
