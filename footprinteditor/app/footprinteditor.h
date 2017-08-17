#ifndef FOOTPRINTEDITOR_H
#define FOOTPRINTEDITOR_H

#include <QMainWindow>
#include "footprinteditor_global.h"

namespace Ui {
    class FootprintEditor;
}

class FOOTPRINTEDITORSHARED_EXPORT FootprintEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit FootprintEditor(QWidget *parent = nullptr);
    ~FootprintEditor();

signals:
    void aboutToQuit();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::FootprintEditor *ui;
};

#endif // FOOTPRINTEDITOR_H
