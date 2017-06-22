#ifndef TABCONTAINER_H
#define TABCONTAINER_H

#include <QTabWidget>

class QMenu;
class QAction;
class SchematicScene;

class TabContainer : public QTabWidget
{
public:
    TabContainer(QWidget *parent = nullptr);


    void changeEditingStatus(bool editing,int index);
    QVector<SchematicScene *> openedSchPage();

    void openSchPage(SchematicScene *page);

//protected:
private slots:
    void postInit();

    void onTabBarRightClicked(int index);

    void onActionSaveTriggered();
    void onActionSaveAllTriggered();
    void onActionCloseTriggered();
    void onActionCloseAllTriggered();
    void onActionCloseAllButThisTriggered();

private:
    int rightClickedIndex;
    QVector<SchematicScene *>openedSchPages;

    QMenu *menu;
    QAction *actionSave;
    QAction *actionSaveAll;
    QAction *actionClose;
    QAction *actionCloseAll;
    QAction *actionCloseAllButThis;

};

#endif // TABCONTAINER_H
