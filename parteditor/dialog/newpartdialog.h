#ifndef NEWPARTDIALOG_H
#define NEWPARTDIALOG_H

#include <QDialog>

namespace Ui {
    class NewPartDialog;
}

class QButtonGroup;

class NewPartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewPartDialog(QWidget *parent = 0);
    ~NewPartDialog();

private slots:
    void onPushButtonOKClicked();
private:
    Ui::NewPartDialog *ui;

    int libCount;
    QButtonGroup *partPackageTypeGroup;
    QButtonGroup *partNumberingGroup;

    void updatePartLibrary();
};

#endif // NEWPARTDIALOG_H
