#include "partlibmanager.h"
#include "ui_partlibmanager.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSqlQueryModel>
#include "db.h"

PartLibManager::PartLibManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PartLibManager)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowCloseButtonHint);
    ui->lineEditSearch->setFocus();

    model = new QSqlQueryModel(this);

    ui->listViewParts->setModel(model);


    // TODO 保存并恢复设置
    currentLibIndex = 0;

    updatePartLibrary();
    updatePartList();

    ui->listViewParts->setModelColumn(1);

    ui->pushButtonRemoveLibrary->setEnabled(false);

    connect(ui->pushButtonAddLibrary,&QPushButton::clicked,
            this,&PartLibManager::onButtonAddLibraryClicked);

    connect(ui->pushButtonRemoveLibrary,&QPushButton::clicked,
            this,&PartLibManager::onButtonRemoveLibraryClicked);

    connect(ui->comboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,[this](int index){
        if(index){
            if(!ui->pushButtonRemoveLibrary->isEnabled()){
               ui->pushButtonRemoveLibrary->setEnabled(true);
            }
        }else{
            ui->pushButtonRemoveLibrary->setEnabled(false);
        }
        currentLibIndex = index;
        updatePartList(getWhere());
    });

    connect(this,&PartLibManager::partLibraryChanged,this,[this](){
        updatePartLibrary();
        updatePartList(getWhere());
    });

    connect(ui->lineEditSearch,&QLineEdit::returnPressed,
            this,&PartLibManager::onButtonSearchClicked);

    connect(ui->pushButtonSearch,&QPushButton::clicked,
            this,&PartLibManager::onButtonSearchClicked);
}

PartLibManager::~PartLibManager()
{
    delete ui;
}

void PartLibManager::onButtonAddLibraryClicked()
{
    const QString filename = QFileDialog::getOpenFileName(this, "打开元件库",
                                                          "H:/eda/eda/specification",
                                                          "元件库 (*.json *.sch)");
    if(!filename.isEmpty()) {
        json library;
        const QString baseName = QFileInfo(filename).baseName();
        bool success = loadJsonDocument(filename,library);

        const QVariantHash result = partLib->get("select libid from part_librarys where libpath=?", {filename});
        int libid;
        // 库不存在则添加 已存在清空该库元件
        if(result.isEmpty()) {
            libid = partLib->insert("insert into part_librarys (libpath,modifiedtime) values (?,?)", {filename,library["libProperty"]["modifiedtime"]});
        } else {
            libid = result.value("libid").toInt();
            partLib->remove("delete from part_parts where libid=?", {libid});
        }

        // 添加元件
        for(auto &p:library["parts"]) {
            const QString partName = p["partName"];
            QVariantList bindValue({partName,partName + ":" + baseName,libid,filename,p["footprint"],md5(p["partName"],filename),QString::fromStdString(p.dump())});
            partLib->insert("insert into part_parts (partname,partalias,libid,libpath,footprint,md5,json) VALUES (?,?,?,?,?,?,?)",bindValue);
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

        partLib->dump("H:/eda/sch.db");
        emit partLibraryChanged();
    }
}

void PartLibManager::onButtonSearchClicked()
{
    updatePartList(getWhere());
}

void PartLibManager::updatePartLibrary()
{
    ui->comboBox->clear();
    ui->comboBox->addItem("所有库",0);
    for(const QVariantHash &r:partLib->select("select * from part_librarys")) {
        ui->comboBox->addItem(r.value("libpath").toString(),r.value("libid"));
    }
    if(ui->comboBox->count() > 1){
        ui->pushButtonRemoveLibrary->setEnabled(true);
    }else{
        ui->pushButtonRemoveLibrary->setEnabled(false);
    }
}

void PartLibManager::updatePartList(const QString &where)
{
    model->setQuery("select partid,partalias from part_parts" + where,partLib->database());
}

QString PartLibManager::getWhere() const
{
    QString where = "";
    where += currentLibIndex ? QString(" where libid=%1").arg(ui->comboBox->currentData().toInt()) : "";

    QString searchText = ui->lineEditSearch->text();
    where += !searchText.isEmpty() ? (where.startsWith(" where") ? " and ": " where ") + QString("partname like '\%%1\%'").arg(searchText) : "";

    return where;
}
