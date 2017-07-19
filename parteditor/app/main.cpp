#include "parteditor.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
//    QApplication::setStyle(QStyleFactory::create("fusion"));

    QApplication a(argc, argv);
    PartEditor w;
    w.show();
    emit w.launched();

    return a.exec();
}
