#ifndef ICONDELEGATE_H
#define ICONDELEGATE_H

#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>

class IconDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit IconDelegate(const QString &iconPath, QObject *parent = nullptr);

protected:
    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QString m_iconPath;
};

#endif // ICONDELEGATE_H
