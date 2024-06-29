#include "operatoritem.h"

#include <QFile>
#include <QIcon>
#include <QVariant>
#include <QDebug>

OperatorItem::OperatorItem(const Operator &op, TreeItem *parent)
    : TreeItem(op.name, parent), m_operator(op) {
}

QVariant OperatorItem::data(int role) const {
    if (role == Qt::DisplayRole) {
        return QString("%1 (%2-%3)").arg(m_operator.name).arg(m_operator.mcc).arg(m_operator.mnc);
    }
    if (role == Qt::UserRole + 2) {
        return m_operator.mcc;
    }
    if (role == Qt::UserRole + 3) {
        return m_operator.mnc;
    }
    return QVariant();
}
