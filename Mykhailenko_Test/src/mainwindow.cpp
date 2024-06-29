#include "mainwindow.h"

#include <QDebug>
#include <QSortFilterProxyModel>
#include <QCoreApplication>

#include "resources/ui_mainwindow.h"
#include "icondelegate.h"
#include "sqlitestorage.h"
#include "treemodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    treeView = new QTreeView(this);
    setCentralWidget(treeView);

    auto storage = std::make_unique<SQLiteStorage>("system.db");
    model = std::make_unique<TreeModel>(std::move(storage), this);

    QString iconPath = ":/Icons";
    qDebug() << "Icon path:" << iconPath;
    IconDelegate *delegate = new IconDelegate(iconPath, this);

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model.get());
    proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->sort(0, Qt::AscendingOrder);

    treeView->setModel(proxyModel);
    treeView->setItemDelegate(delegate);
}

MainWindow::~MainWindow() {
    delete ui;
}
