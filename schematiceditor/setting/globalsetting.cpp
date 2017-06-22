#include "globalsetting.h"

#include "globalsettinggeneral.h"
#include "globalsettingdesign.h"
#include "globalsettingtext.h"
#include "globalsettinglinewidth.h"
#include "globalsettingcolorscheme.h"

GlobalSetting::GlobalSetting(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(651, 500);
    setWindowTitle("全局设置");
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(3);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    treeWidget = new QTreeWidget(this);
    treeWidget->header()->setVisible(false);
    treeWidget->setMaximumWidth(210);

    gridLayout->addWidget(treeWidget, 0, 0, 1, 1);

    stackedWidget = new QStackedWidget(this);
    gridLayout->addWidget(stackedWidget, 0, 1, 1, 2);

    init();
}

void GlobalSetting::init()
{
    QTreeWidgetItem *generalTreeItem = new QTreeWidgetItem(QStringList("General"));
    QTreeWidgetItem *designTreeItem = new QTreeWidgetItem(QStringList("Design"));
    QTreeWidgetItem *textTreeItem = new QTreeWidgetItem(QStringList("Text"));
    QTreeWidgetItem *lineWidthTreeItem = new QTreeWidgetItem(QStringList("Line Width"));
    QTreeWidgetItem *colorSchemeTreeItem = new QTreeWidgetItem(QStringList("Color Scheme"));

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

    GlobalSettingColorScheme *globalSettingColorScheme = new GlobalSettingColorScheme;
    stackedWidget->addWidget(globalSettingColorScheme);
    menuMap.insert(colorSchemeTreeItem,globalSettingColorScheme);

    treeWidget->addTopLevelItem(generalTreeItem);
    treeWidget->addTopLevelItem(designTreeItem);
    treeWidget->addTopLevelItem(textTreeItem);
    treeWidget->addTopLevelItem(lineWidthTreeItem);
    treeWidget->addTopLevelItem(colorSchemeTreeItem);

    connect(treeWidget,&QTreeWidget::currentItemChanged,this,[this](QTreeWidgetItem *item){
        stackedWidget->setCurrentWidget(menuMap.value(item));
    });
}
