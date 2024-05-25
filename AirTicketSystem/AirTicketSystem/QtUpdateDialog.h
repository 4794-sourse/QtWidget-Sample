#pragma once
#include <iostream>
#include <QDialog>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qdialog.h>
#include <QtSql>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include "ui_updateInfo.h"
class QtUpdateDialog  : public QDialog
{
	Q_OBJECT

public:
	QtUpdateDialog(QWidget*parent = NULL);
	~QtUpdateDialog();
signals:
	void dataReady(const QString& arg1, const QString& arg2, const QString& arg3, const QString& arg4, const QString& arg5, const QString& arg6);
public slots:
	void On_Butten();
private:
	QSqlDatabase DB; // 数据库连接
	QSqlTableModel* tabModel; // 数据模型
	Ui::QtticketDialog ui;
};
