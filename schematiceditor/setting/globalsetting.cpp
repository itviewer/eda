#include "globalsetting.h"

#include "globalsettinggeneral.h"
#include "globalsettingdesign.h"
#include "globalsettingtext.h"
#include "globalsettinglinewidth.h"

GlobalSetting::GlobalSetting(QWidget *parent) :
    QWidget(parent)
{
    setWindowModality(Qt::ApplicationModal);
    setFixedSize(550, 450);
    setWindowTitle("全局设置");
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(2);
    gridLayout->setContentsMargins(0, 0, 0, 5);

    treeWidget = new QTreeWidget(this);
    treeWidget->header()->setVisible(false);
    treeWidget->setMaximumWidth(150);

    gridLayout->addWidget(treeWidget, 0, 0, 1, 1);

    stackedWidget = new QStackedWidget(this);
    gridLayout->addWidget(stackedWidget, 0, 1, 1, 2);

    QFrame *frame = new QFrame(this);
    frame->setFrameShadow(QFrame::Sunken);
    frame->setFrameShape(QFrame::HLine);
    gridLayout->addWidget(frame, 1, 0, 1, 3);

    QHBoxLayout *hLayout = new QHBoxLayout;
    buttonOk = new QPushButton("确定",this);
    buttonApply = new QPushButton("应用",this);
    buttonCancel = new QPushButton("取消",this);

    hLayout->addWidget(buttonOk);
    hLayout->addWidget(buttonApply);
    hLayout->addWidget(buttonCancel);

    gridLayout->addLayout(hLayout,2,1,1,2,Qt::AlignHCenter);

    connect(buttonCancel,&QPushButton::clicked, this, &GlobalSetting::close);

    init();
}

void GlobalSetting::init()
{
    QTreeWidgetItem *generalTreeItem = new QTreeWidgetItem({("常规")});
    QTreeWidgetItem *designTreeItem = new QTreeWidgetItem({("设计")});
    QTreeWidgetItem *textTreeItem = new QTreeWidgetItem({("文本")});
    QTreeWidgetItem *lineWidthTreeItem = new QTreeWidgetItem({("线宽")});

    GlobalSettingGeneral *globalSettingGeneral = new GlobalSettingGeneral;
    stackedWidget->addWidget(globalSettingGeneral);
    menuMap.insert(generalTreeItem,globalSettingGeneral);

    GlobalSettingDesign *globalSettingDesign = new GlobalSettingDesign;
    stackedWidget->addWidget(globalSettingDesign);
    menuMap.insert(designTreeItem,globalSettingDesign);

    GlobalSettingText *globalSettingText = new GlobalSettingText;
    stackedWidget->addWidget(globalSettingText);
    menuMap.insert(textTreeItem,globalSettingText);

    GlobalSettingLineWidth *globalSettingLineWidth = new GlobalSettingLineWidth;
    stackedWidget->addWidget(globalSettingLineWidth);
    menuMap.insert(lineWidthTreeItem,globalSettingLineWidth);

    treeWidget->addTopLevelItem(generalTreeItem);
    treeWidget->addTopLevelItem(designTreeItem);
    treeWidget->addTopLevelItem(textTreeItem);
    treeWidget->addTopLevelItem(lineWidthTreeItem);

    connect(treeWidget,&QTreeWidget::currentItemChanged,this,[this](QTreeWidgetItem *item){
        stackedWidget->setCurrentWidget(menuMap.value(item));
    });
}
