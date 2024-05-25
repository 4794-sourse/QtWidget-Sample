#include "QtTicketTui.h"

QtTicketTui::QtTicketTui(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(On_Butten()));
}

void QtTicketTui::On_Butten() {

	QString airline = ui.lineEdit->text();
	QString name = ui.lineEdit_2->text();
	QString number = ui.lineEdit_3->text();
	
	emit dataReady(airline, name, number);
}

QtTicketTui::~QtTicketTui()
{}
