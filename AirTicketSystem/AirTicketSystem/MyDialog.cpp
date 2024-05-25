#include "MyDialog.h"
#include <QMessageBox>
#include <qstring.h>

MyDialog::MyDialog(QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);
}

MyDialog::~MyDialog()
{

}
