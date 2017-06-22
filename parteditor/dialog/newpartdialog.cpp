#include "newpartdialog.h"
#include "ui_newpartdialog.h"
#include <QButtonGroup>
#include <QMessageBox>
#include "global.h"
#include "db.h"

NewPartDialog::NewPartDialog(QWidget *parent) :
    QDialog(parent,Qt::WindowCloseButtonHint),
    ui(new Ui::NewPartDialog)
{
    ui->setupUi(this);

    for(const QString &prefix:partPrefixList){
        ui->comboBoxPartPrefixMap->addItem(partPrefixMap.value(prefix),prefix);
    }
    ui->lineEditPartPrefix->setText("U");
    updatePartLibrary();

    if(ui->comboBoxPartLibraries->count()){
        partLibId = ui->comboBoxPartLibraries->currentData().toInt();
    }

    partPackageTypeGroup = new QButtonGroup(this);
    partPackageTypeGroup->addButton(ui->radioButtonHeterogenous,PackageType::Heterogenous);
    partPackageTypeGroup->addButton(ui->radioButtonHomogeneous,PackageType::Homogeneous);

    partNumberingGroup = new QButtonGroup(this);
    partNumberingGroup->addButton(ui->radioButtonAlphabetic,Numbering::Alphabetic);
    partNumberingGroup->addButton(ui->radioButtonNumeric,Numbering::Numeric);

    connect(ui->lineEditPartName,&QLineEdit::textChanged,this,[this](){
        bool empty = ui->lineEditPartName->text().isEmpty();
        if(empty && ui->pushButtonOK->isEnabled() && libCount){
            ui->pushButtonOK->setDisabled(true);
        }else if(!empty && !ui->pushButtonOK->isEnabled() && libCount){
            ui->pushButtonOK->setDisabled(false);
        }
    });

    connect(ui->pushButtonOK,&QPushButton::clicked,this,&NewPartDialog::onPushButtonOKClicked);
    connect(ui->pushButtonCancel,&QPushButton::clicked,this,[this](){
        reject();
    });

    connect(partPackageTypeGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),this,[this](int id){
        partPackageType = id ;
    });

    connect(partNumberingGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),this,[this](int id){
        partNumbering = id ;
    });

    connect(ui->comboBoxPartLibraries,&QComboBox::currentTextChanged,this,[this](){
        partLibId = ui->comboBoxPartLibraries->currentData().toInt();
    });

    connect(ui->comboBoxPartPrefixMap,&QComboBox::currentTextChanged,this,[this](){
        ui->lineEditPartPrefix->setText(ui->comboBoxPartPrefixMap->currentData().toString());
    });
}

NewPartDialog::~NewPartDialog()
{
    delete ui;
}

void NewPartDialog::onPushButtonOKClicked()
{
    partName = ui->lineEditPartName->text();
    const QVariantHash result = partLib->get("select partid from part_parts where partname=? and libid=?",{partName,partLibId});

    if(!result.isEmpty()){
        QMessageBox::critical(this,"错误！",
                              QString("元件 %1 已存在.\n").arg(partName),
                              QMessageBox::Ok,QMessageBox::Ok);

    }else{
       partPrefix = ui->lineEditPartPrefix->text();
       footprint = ui->lineEditFootprint->text();
       partNumbers = ui->spinBoxPartNumbers->value();

       accept();
    }
}

void NewPartDialog::updatePartLibrary()
{
    for(const QVariantHash &r:partLib->select("select * from part_librarys")) {
        ui->comboBoxPartLibraries->addItem(r.value("libpath").toString(),r.value("libid"));
    }
    libCount = ui->comboBoxPartLibraries->count();
    if(libCount && !ui->lineEditPartName->text().isEmpty()){
       ui->pushButtonOK->setEnabled(true);
    }else{
       ui->pushButtonOK->setEnabled(false);
    }
}
