#include "Calculator_Qt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator_Qt w;
    w.show();
    return a.exec();
}
