#include "QtMyDialog.h"
#include "qmessagebox.h"
QtMyDialog::QtMyDialog(QWidget*parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(On_Butten()));
}

void QtMyDialog::On_Butten() {

	QString dst = ui.lineEdit->text();
	QString number = ui.lineEdit_2->text();
	QString date = ui.lineEdit_3->text();
	QString total = ui.lineEdit_4->text();
	QString unused = ui.lineEdit_5->text();
	QString airline = ui.lineEdit_6->text();
	emit dataReady(dst, number, date, total, unused, airline);
}

QtMyDialog::~QtMyDialog()
{}
