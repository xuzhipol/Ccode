#include "Ccode.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ccode w;
    w.show();
    return a.exec();
}
