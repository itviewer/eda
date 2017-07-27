#ifndef NEWCOLORSCHEMEDIALOG_H
#define NEWCOLORSCHEMEDIALOG_H

#include <QDialog>

namespace Ui {
    class NewColorSchemeDialog;
}

class NewColorSchemeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewColorSchemeDialog(QWidget *parent = 0);
    ~NewColorSchemeDialog();

    QString colorSchemeName() const;
    void setColorSchemeName(const QString &name = "");

private slots:
    void onPushButtonOKClicked();
private:
    Ui::NewColorSchemeDialog *ui;
    QString m_colorSchemeName;
};

#endif // NEWCOLORSCHEMEDIALOG_H
