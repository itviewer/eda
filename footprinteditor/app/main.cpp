#include "footprinteditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FootprintEditor w;
    w.show();

    return a.exec();
}
