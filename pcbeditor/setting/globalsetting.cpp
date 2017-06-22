#include "globalsetting.h"

#include "globalsettinggeneral.h"
#include "globalsettingbackup.h"

GlobalSetting::GlobalSetting(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(651, 500);
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(3);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    treeWidget = new QTreeWidget(this);
    treeWidget->header()->setVisible(false);
    treeWidget->setMaximumWidth(210);

    gridLayout->addWidget(treeWidget, 0, 0, 1, 1);

    stackedWidget = new QStackedWidget(this);
    gridLayout->addWidget(stackedWidget, 0, 1, 1, 2);

//    buttonBox = new QDialogButtonBox(this);
//    buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Ok);

//    gridLayout->addWidget(buttonBox, 1, 1, 1, 1);

    init();
}

GlobalSetting::~GlobalSetting()
{

}

void GlobalSetting::init()
{
    QTreeWidgetItem *globalTreeItem = new QTreeWidgetItem(QStringList("Global"));
    QTreeWidgetItem *generalTreeItem = new QTreeWidgetItem(globalTreeItem,QStringList("General"));
    QTreeWidgetItem *backupTreeItem = new QTreeWidgetItem(globalTreeItem,QStringList("Backup"));

    treeWidget->addTopLevelItem(globalTreeItem);

    GlobalSettingGeneral *globalSettingGeneral = new GlobalSettingGeneral;
    stackedWidget->addWidget(globalSettingGeneral);
    menuMap.insert(globalTreeItem,globalSettingGeneral);
    menuMap.insert(generalTreeItem,globalSettingGeneral);

    GlobalSettingBackup *globalSettingBackup = new GlobalSettingBackup;
    stackedWidget->addWidget(globalSettingBackup);
    menuMap.insert(backupTreeItem,globalSettingBackup);

    connect(treeWidget,&QTreeWidget::currentItemChanged,this,[=](QTreeWidgetItem *item){
        stackedWidget->setCurrentWidget(menuMap.value(item));
    });
}
