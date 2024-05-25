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
    QSqlDatabase DB; // ���ݿ�����
    QSqlTableModel* tabModel; // ����ģ��
    Ui::QMyDialog ui;
};