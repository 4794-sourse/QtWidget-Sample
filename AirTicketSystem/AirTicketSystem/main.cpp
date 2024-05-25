#include "AirTicketSystem.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AirTicketSystem w;
    w.show();
    return a.exec();
}
