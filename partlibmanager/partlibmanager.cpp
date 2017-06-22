#include "partlibmanager.h"
#include "ui_partlibmanager.h"

#include <QFileDialog>
#include <QMessageBox>
#include "db.h"

PartLibManager::PartLibManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PartLibManager)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowCloseButtonHint);

    updatePartLibrary();

    ui->buttonRemoveLibrary->setEnabled(false);

    connect(ui->buttonAddLibrary,&QPushButton::clicked,
            this,&PartLibManager::onButtonAddLibraryClicked);

    connect(ui->buttonRemoveLibrary,&QPushButton::clicked,
            this,&PartLibManager::onButtonRemoveLibraryClicked);

    connect(ui->comboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,[this](int index){
        if(index){
            if(!ui->buttonRemoveLibrary->isEnabled()){
               ui->buttonRemoveLibrary->setEnabled(true);
            }
        }else{
            ui->buttonRemoveLibrary->setEnabled(false);
        }
    });
}

PartLibManager::~PartLibManager()
{
    delete ui;
}

void PartLibManager::onButtonAddLibraryClicked()
{
    const QString filename = QFileDialog::getOpenFileName(this, "打开元件库",
                                                          "H:/eda/eda/SchematicEditor/test",
                                                          "元件库 (*.json *.sch)");
    if(!filename.isEmpty()) {
        json library;
        bool success = loadJsonDocument(filename,library);

        const QVariantHash result = partLib->get("select libid from part_librarys where libpath=?", {filename});
        int libid;
        // 库不存在则添加 已存在清空该库元件
        if(result.isEmpty()) {
            libid = partLib->insert("insert into part_librarys (libpath) values (?)", {filename});
            updatePartLibrary();
        } else {
            libid = result.value("libid").toInt();
            partLib->remove("delete from part_parts where libid=?", {libid});
        }

        // 添加元件
        for(auto &p:library) {
            QVariantList bindValue({p["partName"],libid,filename,p["footprint"],md5(p["partName"],filename),QString::fromStdString(p.dump())});
            partLib->insert("insert into part_parts (partname,libid,libpath,footprint,md5,json) VALUES (?,?,?,?,?,?)",bindValue);
        }

        partLib->dump("H:/eda/sch.db");
        emit partLibraryChanged();
    }
}

void PartLibManager::onButtonRemoveLibraryClicked()
{
    int ret = QMessageBox::question(this, "提示",
                                    QString("确认删除元件库\n"
                                            "%1").arg(ui->comboBox->currentText()),
                                    QMessageBox::Ok | QMessageBox::Cancel,
                                    QMessageBox::Ok);

    if(ret == QMessageBox::Ok){
        int libid = ui->comboBox->currentData().toInt();
        // 外键自动删除元件
        partLib->remove("delete from part_librarys where libid=?",{libid});

        updatePartLibrary();
        partLib->dump("H:/eda/sch.db");
        emit partLibraryChanged();
    }
}

void PartLibManager::updatePartLibrary()
{
    ui->comboBox->clear();
    ui->comboBox->addItem("所有库",0);
    for(const QVariantHash &r:partLib->select("select * from part_librarys")) {
        ui->comboBox->addItem(r.value("libpath").toString(),r.value("libid"));
    }
    if(ui->comboBox->count() > 1){
        ui->buttonRemoveLibrary->setEnabled(true);
    }else{
        ui->buttonRemoveLibrary->setEnabled(false);
    }
}
