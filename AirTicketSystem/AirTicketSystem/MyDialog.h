#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qdialog.h>
#include <QtSql>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include "ui_DialogButtonBottom.h"

class MyDialog : public QDialog
{
    Q_OBJECT
public:
    MyDialog(QWidget* parent = nullptr);
    ~MyDialog();

private:
    QSqlDatabase DB; // 数据库连接
    QSqlTableModel* tabModel; // 数据模型
    Ui::QMyDialog ui;
};