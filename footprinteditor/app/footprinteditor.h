#ifndef FOOTPRINTEDITOR_H
#define FOOTPRINTEDITOR_H

#include <QMainWindow>

namespace Ui {
    class FootprintEditor;
}

class FootprintEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit FootprintEditor(QWidget *parent = 0);
    ~FootprintEditor();

private:
    Ui::FootprintEditor *ui;
};

#endif // FOOTPRINTEDITOR_H
