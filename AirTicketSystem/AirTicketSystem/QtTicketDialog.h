#pragma once
#include <iostream>
#include <QDialog>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qdialog.h>
#include <QtSql>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include "ui_ticketinfo.h"

class QtTicketDialog  : public QDialog
{
	Q_OBJECT

public:
	QtTicketDialog(QWidget *parent = NULL);
	~QtTicketDialog();
signals:
	void dataReady(const QString& arg1, const QString& arg2, const QString& arg3, const QString& arg4);
public slots:
	void On_Butten();
private:
	QSqlDatabase DB; // 数据库连接
	QSqlTableModel* tabModel; // 数据模型
	Ui::Dialog ui;
};
