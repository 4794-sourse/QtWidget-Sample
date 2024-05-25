#include "AirTicketSystem.h"
#include <QtSql>
#include <QStandardItemModel>
#include <QMessageBox>
#include <qstring.h>

AirTicketSystem::AirTicketSystem(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    DB = QSqlDatabase::addDatabase("QSQLITE"); //添加 SQLITE 数据库驱动
    DB.setDatabaseName("./ticketinfo.db"); //设置数据库名称
    if (!DB.open()) {//打开数据库失败
        QMessageBox::warning(this, tr("错误"), tr("打开数据库失败，请检测数据库文件！"));
    } else {

        tabModel = new QSqlTableModel(this, DB); //数据模型
        tabModel->setTable("AirlineInfo"); //设置数据表
        tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit); //数据保存方式
        if (!(tabModel->select())) //查询数据失败
        {
            QMessageBox::critical(this, tr("错误信息"), tr("打开数据表错误,错误信息:\n") + tabModel->lastError().text());
        }
        ui.tableView->setModel(tabModel);
    }
    mytuidia = new QtTicketTui();
    myticketdia = new QtTicketDialog();
    myupdatedia = new QtUpdateDialog();
    mydia = new QtMyDialog();

    connect(mytuidia, SIGNAL(dataReady(QString, QString, QString)), this, SLOT(On_ticketTui(QString, QString, QString)));
    connect(myticketdia, SIGNAL(dataReady(QString, QString, QString, QString)), this, SLOT(On_ticketReally(QString, QString, QString, QString)));
    connect(myupdatedia, SIGNAL(dataReady(QString, QString, QString, QString, QString, QString)), this, SLOT(On_UpdateinfoReally(QString, QString, QString, QString, QString, QString)));
    connect(mydia, SIGNAL(dataReady(QString,QString, QString, QString, QString, QString)), this, SLOT(On_AddinfoReally(QString, QString, QString, QString, QString, QString)));
    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(On_Airline()));
    connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(On_Addinfo()));
    connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(On_updateinfo()));
    connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(On_ticket()));
    connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(On_Tui()));
    connect(ui.pushButton_6, SIGNAL(clicked()), this, SLOT(On_HoubuInfo()));
    connect(ui.pushButton_7, SIGNAL(clicked()), this, SLOT(On_SearchInfo()));
    connect(ui.pushButton_8, SIGNAL(clicked()), this, SLOT(On_ticketInfo()));
}

void AirTicketSystem::On_Tui() {
    mytuidia->exec();
    On_Airline();
}

void AirTicketSystem::On_ticketTui(QString arg1, QString arg2, QString arg3) {

    QSqlQuery query;

    // 准备SELECT语句
    query.prepare("SELECT * FROM ticketinfo WHERE 航班号 = ? AND 姓名 = ?");

    // 绑定参数
    query.addBindValue(arg1);
    query.addBindValue(arg2);

    // 执行SELECT操作
    if (query.exec()) {
        if (query.next()) {

            int ticketQuantityTotal = query.value("订票量").toInt();
            int ticketQuantity = ticketQuantityTotal + arg3.toInt();

            {
                QSqlQuery query;

                // 准备更新语句
                query.prepare("UPDATE AirlineInfo SET 余票量 = ? WHERE 航班号 = ?");

                // 绑定参数 
                query.addBindValue(ticketQuantity);
                query.addBindValue(arg1);

                // 执行更新操作
                if (query.exec()) {
                    if (query.numRowsAffected() > 0) {
                        //QMessageBox::information(this, tr("成功"), tr("更新成功"));
                    }
                    else {
                        QMessageBox::warning(this, tr("警告"), tr("没有找到匹配的记录"));
                    }
                }
                else {
                    QMessageBox::critical(this, tr("错误信息"), query.lastError().text());
                }
            }

            {
                QSqlQuery query;

                // 准备更新语句
                query.prepare("UPDATE ticketinfo SET 订票量 = ? WHERE 航班号 = ?");

                int num = ticketQuantityTotal - arg3.toInt();
                // 绑定参数 
                query.addBindValue(num);
                query.addBindValue(arg1);

                // 执行更新操作
                if (query.exec()) {
                    if (query.numRowsAffected() > 0) {
                        //QMessageBox::information(this, tr("成功"), tr("更新成功"));
                    }
                    else {
                        QMessageBox::warning(this, tr("警告"), tr("没有找到匹配的记录"));
                    }
                }
                else {
                    QMessageBox::critical(this, tr("错误信息"), query.lastError().text());
                }

            }
            QMessageBox::information(this, tr("成功"), tr("退票成功"));
        }
        else {
            QMessageBox::warning(this, tr("警告"), tr("没有找到匹配的记录"));
        }
    }
    else {
        QMessageBox::critical(this, tr("错误信息"), query.lastError().text());
    }

}

void AirTicketSystem::On_ticket() {
    myticketdia->exec();
    On_Airline();
}
void AirTicketSystem::On_ticketReally(QString arg1, QString arg2, QString arg3, QString arg4) {
    
    QSqlQuery query;

    // 准备SELECT语句
    query.prepare("SELECT * FROM AirlineInfo WHERE 航班号 = ?");

    // 绑定参数
    query.addBindValue(arg1);

    // 执行SELECT操作
    if (query.exec()) {
        if (query.next()) {
            
            int ticketQuantity = query.value("余票量").toInt();
            if (ticketQuantity >= arg3.toInt()) {

                {
                    QSqlQuery query;
                    // 准备插入语句
                    query.prepare("INSERT INTO ticketinfo (航班号, 姓名, 订票量, 等级) "
                        "VALUES (?, ?, ?, ?)");

                    // 绑定参数
                    query.addBindValue(arg1);
                    query.addBindValue(arg2);
                    query.addBindValue(arg3.toInt());
                    query.addBindValue(arg4.toInt());
                    // 执行插入操作
                    if (query.exec()) {
                        //QMessageBox::information(this, tr("成功"), tr("插入成功"));
                    }
                    else {
                        QMessageBox::critical(this, tr("错误信息"), query.lastError().text());
                    }
                }

                {
                    QSqlQuery query;

                    // 准备更新语句
                    query.prepare("UPDATE AirlineInfo SET 余票量 = ? WHERE 航班号 = ?");

                    int num = ticketQuantity - arg3.toInt();
                    // 绑定参数 
                    query.addBindValue(num);
                    query.addBindValue(arg1);

                    // 执行更新操作
                    if (query.exec()) {
                        if (query.numRowsAffected() > 0) {
                            //QMessageBox::information(this, tr("成功"), tr("更新成功"));
                        }
                        else {
                            QMessageBox::warning(this, tr("警告"), tr("没有找到匹配的记录"));
                        }
                    }
                    else {
                        QMessageBox::critical(this, tr("错误信息"), query.lastError().text());
                    }
                }

                QMessageBox::information(this, tr("成功"), tr("订票成功"));
            }
            else {

                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "警告", "余票不足，是否添加后补?", QMessageBox::Yes | QMessageBox::No);

               
                if (reply == QMessageBox::Yes) {
                   
                    {
                        QSqlQuery query;
                        // 准备插入语句
                        query.prepare("INSERT INTO HouBuInfo (航班号, 姓名, 订票量) "
                            "VALUES (?, ?, ?)");

                        // 绑定参数
                        query.addBindValue(arg1);
                        query.addBindValue(arg2);
                        query.addBindValue(arg3.toInt());
                        // 执行插入操作
                        if (query.exec()) {
                            QMessageBox::information(this, tr("成功"), tr("添加成功"));
                        }
                        else {
                            QMessageBox::critical(this, tr("错误信息"), query.lastError().text());
                        }
                    }

                }
            }
        }
        else {
            QMessageBox::warning(this, tr("警告"), tr("没有找到匹配的记录"));
        }
    }
    else {
        QMessageBox::critical(this, tr("错误信息"), query.lastError().text());
    }

}

void AirTicketSystem::On_ticketInfo() {

    tabModel->setTable("ticketinfo"); //设置数据表
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit); //数据保存方式
    if (!(tabModel->select())) //查询数据失败
    {
        QMessageBox::critical(this, tr("错误信息"), tr("打开数据表错误,错误信息:\n") + tabModel->lastError().text());
    }
    ui.tableView->setModel(tabModel);
}

void AirTicketSystem::On_updateinfo() {
    myupdatedia->exec();
    On_Airline();
}

void AirTicketSystem::On_UpdateinfoReally(const QString& arg1, const QString& arg2, const QString& arg3, const QString& arg4, const QString& arg5, const QString& arg6) {

    QSqlQuery query;

    // 准备更新语句
    query.prepare("UPDATE AirlineInfo SET 终点 = ?, 飞机号 = ?, 飞行日期 = ?, 乘员定额 = ?, 余票量 = ? WHERE 航班号 = ?");

    // 绑定参数 
    query.addBindValue(arg2);
    query.addBindValue(arg3);
    query.addBindValue(arg4);
    query.addBindValue(arg5.toInt());
    query.addBindValue(arg5.toInt());
    query.addBindValue(arg1);

    // 执行更新操作
    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            QMessageBox::information(this, tr("成功"), tr("更新成功"));
        }
        else {
            QMessageBox::warning(this, tr("警告"), tr("没有找到匹配的记录"));
        }
    }
    else {
        QMessageBox::critical(this, tr("错误信息"), query.lastError().text());
    }
}

void AirTicketSystem::On_AddinfoReally(const QString& arg1, const QString& arg2, const QString& arg3, const QString& arg4, const QString& arg5, const QString& arg6)
{
    // 创建数据库查询对象
    QSqlQuery query;

    // 准备插入语句
    query.prepare("INSERT INTO AirlineInfo (终点, 航班号, 飞机号, 飞行日期, 乘员定额, 余票量) "
        "VALUES (?, ?, ?, ?, ?, ?)");

    // 绑定参数
    query.addBindValue(arg1);
    query.addBindValue(arg6);
    query.addBindValue(arg2);
    query.addBindValue(arg3);
    query.addBindValue(arg4.toInt());
    query.addBindValue(arg5.toInt());

    // 执行插入操作
    if (query.exec()) {
        QMessageBox::information(this, tr("成功"), tr("插入成功"));
    }
    else {
        QMessageBox::critical(this, tr("错误信息"), query.lastError().text());
    }
}

void AirTicketSystem::On_Addinfo() {
    mydia->exec();
    On_Airline();
}

void AirTicketSystem::On_SearchInfo() {
    
    On_Airline();
    QString str = ui.lineEdit->text();
    if (str.length()) {
        QString flt = QString(" 航班号='%1' ").arg(str);
        tabModel->setFilter(flt);
        tabModel->select();
        ui.tableView->setModel(tabModel);
    }
    else {
        QMessageBox::critical(this, tr("错误信息"), "请填写检索信息");
    }
}

void AirTicketSystem::On_Airline() {
    tabModel->setTable("AirlineInfo"); //设置数据表
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit); //数据保存方式
    if (!(tabModel->select())) //查询数据失败
    {
        QMessageBox::critical(this, tr("错误信息"), tr("打开数据表错误,错误信息:\n") + tabModel->lastError().text());
    }
    ui.tableView->setModel(tabModel);
}

void AirTicketSystem::On_HoubuInfo() {
    tabModel->setTable("HouBuInfo"); //设置数据表
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit); //数据保存方式
    if (!(tabModel->select())) //查询数据失败
    {
        QMessageBox::critical(this, tr("错误信息"), tr("打开数据表错误,错误信息:\n") + tabModel->lastError().text());
    }
    ui.tableView->setModel(tabModel);
}

AirTicketSystem::~AirTicketSystem()
{

}
