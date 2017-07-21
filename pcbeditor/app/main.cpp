#include "pcbeditor.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
//    QApplication::setStyle(QStyleFactory::create("fusion"));
//    QPalette palette;
//    palette.setColor(QPalette::Window, QColor(53,53,53));
//    palette.setColor(QPalette::WindowText, Qt::white);
//    palette.setColor(QPalette::Base, QColor(15,15,15));
//    palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
//    palette.setColor(QPalette::ToolTipBase, Qt::white);
//    palette.setColor(QPalette::ToolTipText, Qt::white);
//    palette.setColor(QPalette::Text, Qt::white);
//    palette.setColor(QPalette::Button, QColor(53,53,53));
//    palette.setColor(QPalette::ButtonText, Qt::white);
//    palette.setColor(QPalette::BrightText, Qt::red);

////    palette.setColor(QPalette::Highlight, Qt::blue);
//    palette.setColor(QPalette::HighlightedText, Qt::black);
//    QApplication::setPalette(palette);

    QApplication a(argc, argv);
    PCBEditor w;
    w.show();
    emit w.launch();

    return a.exec();
}
