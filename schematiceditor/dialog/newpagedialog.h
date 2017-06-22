#ifndef NEWPAGEDIALOG_H
#define NEWPAGEDIALOG_H

#include <QDialog>

namespace Ui {
    class NewPageDialog;
}

class NewPageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewPageDialog(QWidget *parent = 0);
    ~NewPageDialog();

    QString getPageName() const;
    void setPageName(const QString &name = "");

    int getIndex() const;
    void setIndex(int index);

private slots:
    void onPushButtonOKClicked();
private:
    Ui::NewPageDialog *ui;
    QString pageName;
    int index;
};

#endif // NEWPAGEDIALOG_H
