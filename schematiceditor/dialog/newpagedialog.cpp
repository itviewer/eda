#include "newpagedialog.h"
#include "ui_newpagedialog.h"
#include <QMessageBox>
#include "global.h"

NewPageDialog::NewPageDialog(QWidget *parent) :
    QDialog(parent,Qt::WindowCloseButtonHint),
    ui(new Ui::NewPageDialog)
{
    ui->setupUi(this);
    setWindowTitle("新建原理图页");
    ui->pushButtonOK->setDisabled(true);

    connect(ui->lineEditName,&QLineEdit::textChanged,this,[this](){
        bool empty = ui->lineEditName->text().isEmpty();
        if(empty && ui->pushButtonOK->isEnabled()){
            ui->pushButtonOK->setEnabled(false);
        }else if(!empty && !ui->pushButtonOK->isEnabled()){
            ui->pushButtonOK->setEnabled(true);
        }
    });


    connect(ui->pushButtonOK,&QPushButton::clicked,this,&NewPageDialog::onPushButtonOKClicked);
    connect(ui->pushButtonCancel,&QPushButton::clicked,this,&NewPageDialog::reject);
}

NewPageDialog::~NewPageDialog()
{
    delete ui;
}

QString NewPageDialog::getPageName() const
{
    return pageName;
}

void NewPageDialog::setPageName(const QString &name)
{
    if(name.isEmpty()){
        ui->lineEditName->clear();
    }else{
        ui->lineEditName->setText(name);
    }
    ui->lineEditName->setFocus();
}

int NewPageDialog::getIndex() const
{
    return index;
}

void NewPageDialog::setIndex(int index)
{
    ui->spinBoxIndex->setValue(index);
}

void NewPageDialog::onPushButtonOKClicked()
{
    pageName = ui->lineEditName->text();

    if(schPages.keys().contains(pageName)){
        QMessageBox::critical(this,"错误！",
                              QString("原理图页 %1 已存在.\n").arg(pageName),
                              QMessageBox::Ok,QMessageBox::Ok);

    }else{
        index = ui->spinBoxIndex->value();
        accept();
    }
}
