#include "newcolorschemedialog.h"
#include "ui_newcolorschemedialog.h"
#include <QMessageBox>
#include "global.h"

NewColorSchemeDialog::NewColorSchemeDialog(QWidget *parent) :
    QDialog(parent,Qt::WindowCloseButtonHint),
    ui(new Ui::NewColorSchemeDialog)
{
    ui->setupUi(this);
    setWindowTitle("新建颜色方案");
    ui->pushButtonOK->setDisabled(true);

    connect(ui->lineEditColorScheme,&QLineEdit::textChanged,this,[this](){
        bool empty = ui->lineEditColorScheme->text().isEmpty();
        if(empty && ui->pushButtonOK->isEnabled()){
            ui->pushButtonOK->setEnabled(false);
        }else if(!empty && !ui->pushButtonOK->isEnabled()){
            ui->pushButtonOK->setEnabled(true);
        }
    });

    connect(ui->pushButtonOK,&QPushButton::clicked,this,&NewColorSchemeDialog::onPushButtonOKClicked);
    connect(ui->pushButtonCancel,&QPushButton::clicked,this,&NewColorSchemeDialog::reject);
}

NewColorSchemeDialog::~NewColorSchemeDialog()
{
    delete ui;
}

QString NewColorSchemeDialog::colorSchemeName() const
{
    return m_colorSchemeName;
}

void NewColorSchemeDialog::setColorSchemeName(const QString &name)
{

}

void NewColorSchemeDialog::onPushButtonOKClicked()
{
    m_colorSchemeName = ui->lineEditColorScheme->text();
    if(schColorScheme.contains(m_colorSchemeName)){
        QMessageBox::critical(this,"错误！",
                              QString("颜色方案 %1 已存在.\n").arg(m_colorSchemeName),
                              QMessageBox::Ok,QMessageBox::Ok);

    }else{
        accept();
    }
}
