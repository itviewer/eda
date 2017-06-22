#ifndef GLOBALSETTINGDESIGN_H
#define GLOBALSETTINGDESIGN_H

#include <QWidget>

namespace Ui {
    class GlobalSettingDesign;
}

class GlobalSettingDesign : public QWidget
{
    Q_OBJECT

public:
    explicit GlobalSettingDesign(QWidget *parent = 0);
    ~GlobalSettingDesign();

private:
    Ui::GlobalSettingDesign *ui;
};

#endif // GLOBALSETTINGDESIGN_H
