#ifndef GLOBALSETTING_H
#define GLOBALSETTING_H

#include <QtWidgets>

class GlobalSetting : public QWidget
{
    Q_OBJECT

public:
    explicit GlobalSetting(QWidget *parent = 0);
    ~GlobalSetting();

private:
    QGridLayout *gridLayout;
    QTreeWidget *treeWidget;
    QStackedWidget *stackedWidget;
//    QDialogButtonBox *buttonBox;

    inline void init();

    QHash<QTreeWidgetItem *,QWidget *> menuMap;
};

#endif // GLOBALSETTING_H
