#pragma once

#include <QtWidgets/QMainWindow>
#include <QtSql>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include "ui_AirTicketSystem.h"
#include "QtMyDialog.h"
#include "QtUpdateDialog.h"
#include "QtTicketDialog.h"
#include "QtTicketTui.h"
class AirTicketSystem : public QMainWindow
{
    Q_OBJECT

public:
    AirTicketSystem(QWidget *parent = nullptr);
    ~AirTicketSystem();
public slots:
    void On_Airline();
    void On_HoubuInfo();
    void On_Addinfo();
    void On_updateinfo();
    void On_SearchInfo();
    void On_ticketInfo();
    void On_ticket();
    void On_Tui();
    void On_ticketTui(QString arg1, QString arg2, QString arg3);
    void On_ticketReally(QString, QString, QString, QString);
    void On_AddinfoReally(const QString& arg1, const QString& arg2, const QString& arg3, const QString& arg4, const QString& arg5, const QString& arg6);
    void On_UpdateinfoReally(const QString& arg1, const QString& arg2, const QString& arg3, const QString& arg4, const QString& arg5, const QString& arg6);
private:
    QtTicketTui* mytuidia;
    QtTicketDialog* myticketdia;
    QtUpdateDialog* myupdatedia;
    QtMyDialog *mydia;
    QSqlDatabase DB; //数据库连接
    QSqlTableModel* tabModel; //数据模型
    Ui::AirTicketSystemClass ui;
};
