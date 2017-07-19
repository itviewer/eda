#include "controlcenter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ControlCenter w;
    w.show();

    return a.exec();
}
