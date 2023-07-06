#include "Calculator_Qt.h"
#include <QApplication>
#include <QWidget>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Calculator_Qt window;
    window.setFixedSize(300, 600);
    window.show();

    return app.exec();
}
