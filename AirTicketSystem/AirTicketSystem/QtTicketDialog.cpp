#include "QtTicketDialog.h"

QtTicketDialog::QtTicketDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(On_Butten()));
}


void QtTicketDialog::On_Butten() {

	QString airline = ui.lineEdit->text();
	QString name = ui.lineEdit_2->text();
	QString number = ui.lineEdit_3->text();
	QString level = ui.lineEdit_4->text();
	
	emit dataReady(airline, name, number, level);
}

QtTicketDialog::~QtTicketDialog()
{}
