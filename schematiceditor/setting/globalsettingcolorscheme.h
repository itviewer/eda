#ifndef GLOBALSETTINGCOLORSCHEME_H
#define GLOBALSETTINGCOLORSCHEME_H

#include <QWidget>

namespace Ui {
    class GlobalSettingColorScheme;
}

class GlobalSettingColorScheme : public QWidget
{
    Q_OBJECT

public:
    explicit GlobalSettingColorScheme(QWidget *parent = 0);
    ~GlobalSettingColorScheme();

private:
    Ui::GlobalSettingColorScheme *ui;
};

#endif // GLOBALSETTINGCOLORSCHEME_H
