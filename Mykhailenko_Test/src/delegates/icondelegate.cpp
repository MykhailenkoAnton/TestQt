#include "icondelegate.h"
#include <QFile>
#include <QIcon>
#include <QStyleOptionViewItem>
#include <QPainter>
#include <QDebug>

IconDelegate::IconDelegate(const QString &iconPath, QObject *parent)
    : QStyledItemDelegate(parent), m_iconPath(iconPath) {}

void IconDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const {
    QStyledItemDelegate::initStyleOption(option, index);

    QString filePath;
    if (index.parent().isValid()) {
        int mcc = index.data(Qt::UserRole + 2).toInt();
        int mnc = index.data(Qt::UserRole + 3).toInt();
        filePath = QString(":/Icons/%1_%2.png").arg(mcc).arg(mnc);
        qDebug() << "Operator icon path:" << filePath;
    } else {
        QString countryCode = index.data(Qt::UserRole + 4).toString();
        filePath = QString(":/Icons/%1.png").arg(countryCode);
        qDebug() << "Country icon path:" << filePath;
    }

    if (QFile::exists(filePath)) {
        option->icon = QIcon(filePath);
        qDebug() << "Icon found and applied:" << filePath;
    } else {
        qDebug() << "Icon not found at:" << filePath;
    }
}

void IconDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    painter->save();

    if (!opt.icon.isNull()) {
        QRect iconRect = opt.rect;
        iconRect.setWidth(opt.rect.height());
        opt.icon.paint(painter, iconRect, Qt::AlignLeft | Qt::AlignVCenter);

        opt.rect.setLeft(iconRect.right() + 5);
    }

    QStyledItemDelegate::paint(painter, opt, index);

    painter->restore();
}
