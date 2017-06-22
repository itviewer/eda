#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <QTreeWidget>

class SchematicScene;
class SchematicNavigator;
class PartTypeNavigator;
class PartNavigator;
class NetNavigator;

class SchTreeWidgetItem;

class Navigator : public QTreeWidget
{
    Q_OBJECT

public:
    Navigator(QWidget *parent = nullptr);
    ~Navigator();

    void addSchPage(SchematicScene *scene);
    void removeSchPage(const QString &pageName);
    int getMaxSchPageIndex();


    QSize sizeHint() const;
    void createNavigator();

public slots:
//    void onSchPageAdded();
protected:
    void mouseMoveEvent(QMouseEvent *event);// 阻止滑动选择

private slots:
    void onCurrentItemChanged(QTreeWidgetItem *item);

private:
    SchematicNavigator *schNavigator;
    PartTypeNavigator *partTypeNavigator;
    PartNavigator *partNavigator;
    NetNavigator *netNavigator;

    QVector<SchTreeWidgetItem *> schPageTree;

    void createSchPageTree();
    void createPartTypeTree();
    void createPartTree();
    void createNetTree();
};

#endif // NAVIGATOR_H
