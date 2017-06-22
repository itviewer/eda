#include "tabcontainer.h"
#include "schematiceditor.h"
#include "schematicview.h"
#include "schematicscene.h"
#include <QDebug>
#include <QAction>
#include <QTabBar>
#include <QMenu>

TabContainer::TabContainer(QWidget *parent)
    :QTabWidget(parent),
    rightClickedIndex(-1)
{
    connect(this, &TabContainer::currentChanged,
            schEditor, &SchematicEditor::onCurrentViewChanged);

    connect(schEditor,&SchematicEditor::launched,
            this,&TabContainer::postInit);

    connect(schEditor,&SchematicEditor::pageAdded,this,[this](SchematicScene *page){
        openedSchPages.append(page);
    });
}

void TabContainer::changeEditingStatus(bool editing,int index)
{
    if(editing){
       setTabText(index,QString("%1%2").arg(tabText(index)).arg('*'));
    }else{
       setTabText(index,QString("%1").arg(tabText(index).remove(-1,1)));
    }
}

QVector<SchematicScene *> TabContainer::openedSchPage()
{
    return openedSchPages;
}

void TabContainer::openSchPage(SchematicScene *page)
{
    if(!openedSchPages.contains(page)){
        addTab(page->schView,page->pageProperty["pageName"]);
        openedSchPages.append(page);
    }
    setCurrentWidget(page->schView);
}

void TabContainer::postInit()
{
    setContextMenuPolicy(Qt::PreventContextMenu);

    connect(tabBar(),&QTabBar::tabBarRightClicked,
            this,&TabContainer::onTabBarRightClicked);

    menu = new QMenu(this);

    actionClose = new QAction("Close",this);
    connect(actionClose,&QAction::triggered,
            this,&TabContainer::onActionCloseTriggered);
    menu->addAction(actionClose);

    actionCloseAll = new QAction("Close All",this);
    connect(actionCloseAll,&QAction::triggered,
            this,&TabContainer::onActionCloseAllTriggered);
    menu->addAction(actionCloseAll);

    actionCloseAllButThis = new QAction("Close All But This",this);
    connect(actionCloseAllButThis,&QAction::triggered,
            this,&TabContainer::onActionCloseAllButThisTriggered);
    menu->addAction(actionCloseAllButThis);

    menu->addSeparator();

    actionSave = new QAction("Save",this);
    connect(actionSave,&QAction::triggered,
            this,&TabContainer::onActionSaveTriggered);
    menu->addAction(actionSave);

    actionSaveAll = new QAction("Save All",this);
    connect(actionSaveAll,&QAction::triggered,
            this,&TabContainer::onActionSaveAllTriggered);
    menu->addAction(actionSaveAll);
}

void TabContainer::onTabBarRightClicked(int index)
{
    rightClickedIndex = index;
    menu->exec(QCursor::pos());
}

void TabContainer::onActionSaveTriggered()
{
    qDebug()<<rightClickedIndex;
}

void TabContainer::onActionSaveAllTriggered()
{

}

void TabContainer::onActionCloseTriggered()
{
    SchematicView *view = qobject_cast<SchematicView*>(widget(rightClickedIndex));
    removeTab(rightClickedIndex);
    if(view){
        openedSchPages.removeOne(view->schScene);;
    }
}

void TabContainer::onActionCloseAllTriggered()
{
    qDebug()<<rightClickedIndex;
    openedSchPages.clear();
}

void TabContainer::onActionCloseAllButThisTriggered()
{
    qDebug()<<rightClickedIndex;
}
