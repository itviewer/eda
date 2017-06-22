#ifndef GLOBALSETTINGTEXT_H
#define GLOBALSETTINGTEXT_H

#include <QWidget>

namespace Ui {
    class GlobalSettingText;
}

class GlobalSettingText : public QWidget
{
    Q_OBJECT

public:
    explicit GlobalSettingText(QWidget *parent = 0);
    ~GlobalSettingText();

private:
    Ui::GlobalSettingText *ui;
};

#endif // GLOBALSETTINGTEXT_H
