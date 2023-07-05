#include "Calculator_Qt.h"
#include <QApplication>
#include <QWidget>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Calculator_Qt window;
    window.show();

    return app.exec();
}
