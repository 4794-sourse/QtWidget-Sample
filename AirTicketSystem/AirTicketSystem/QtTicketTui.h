#pragma once
#include <iostream>
#include <QDialog>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qdialog.h>
#include <QtSql>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include "ui_DialogButtonBottom1.h"

class QtTicketTui  : public QDialog
{
	Q_OBJECT

public:
	QtTicketTui(QWidget *parent = NULL);
	~QtTicketTui();
signals:
	void dataReady(const QString& arg1, const QString& arg2, const QString& arg3);
public slots:
	void On_Butten();
private:
	QSqlDatabase DB; // 数据库连接
	QSqlTableModel* tabModel; // 数据模型
	Ui::DialogTui ui;
};
