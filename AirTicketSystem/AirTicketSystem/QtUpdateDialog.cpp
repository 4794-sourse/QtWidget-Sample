#include "QtUpdateDialog.h"

QtUpdateDialog::QtUpdateDialog(QWidget*parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(On_Butten()));
}

void QtUpdateDialog::On_Butten() {

	QString airline = ui.lineEdit->text();
	QString dest = ui.lineEdit_2->text();
	QString number = ui.lineEdit_3->text();
	QString data = ui.lineEdit_4->text();
	QString total = ui.lineEdit_5->text();
	QString unused = ui.lineEdit_6->text();
	emit dataReady(airline, dest, number, data, total, unused);
}

QtUpdateDialog::~QtUpdateDialog()
{}
