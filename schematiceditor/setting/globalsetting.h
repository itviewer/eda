#ifndef GLOBALSETTING_H
#define GLOBALSETTING_H

#include <QtWidgets>

class GlobalSetting : public QWidget
{
    Q_OBJECT
public:
    explicit GlobalSetting(QWidget *parent = 0);

signals:

public slots:
private:
    QGridLayout *gridLayout;
    QTreeWidget *treeWidget;
    QStackedWidget *stackedWidget;

    inline void init();

    QHash<QTreeWidgetItem *,QWidget *> menuMap;
};

#endif // GLOBALSETTING_H
