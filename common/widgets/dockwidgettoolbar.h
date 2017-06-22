#ifndef DOCKWIDGETTOOLBAR_H
#define DOCKWIDGETTOOLBAR_H

#include <QToolBar>

class DockWidget;

class DockWidgetToolBar : public QToolBar
{
    Q_OBJECT

public:
    DockWidgetToolBar(const Qt::Orientation &orientation,QWidget *parent = nullptr);

    QHash<DockWidget *,QAction *> dockWidgetButtons;
    void addDockWidget(DockWidget *widget);
    void removeDockWidget(DockWidget *widget);
private:
    Qt::Orientation orientation;
};

#endif // DOCKWIDGETTOOLBAR_H
