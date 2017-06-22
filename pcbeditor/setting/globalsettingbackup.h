#ifndef GLOBALSETTINGBACKUP_H
#define GLOBALSETTINGBACKUP_H

#include <QWidget>

namespace Ui {
    class GlobalSettingBackup;
}

class GlobalSettingBackup : public QWidget
{
    Q_OBJECT

public:
    explicit GlobalSettingBackup(QWidget *parent = 0);
    ~GlobalSettingBackup();

private:
    Ui::GlobalSettingBackup *ui;
};

#endif // GLOBALSETTINGBACKUP_H
