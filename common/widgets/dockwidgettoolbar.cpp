#include "dockwidgettoolbar.h"
#include "dockwidget.h"
#include "dockwidgetpushbutton.h"
#include <QDebug>
DockWidgetToolBar::DockWidgetToolBar(const Qt::Orientation &orientation,QWidget *parent)
    :QToolBar(parent),
      orientation(orientation)
{
    setFloatable(false);
    setMovable(false);
}

void DockWidgetToolBar::addDockWidget(DockWidget *widget)
{
    DockWidgetPushButton *button = new DockWidgetPushButton(widget->windowTitle(),orientation);
    QAction *action = addWidget(button);
    dockWidgetButtons.insert(widget,action);
//    addAction(button);
    connect(button,&DockWidgetPushButton::hoverEntered,
            widget,&DockWidget::onDockButtonEntered);
    connect(button,&DockWidgetPushButton::hoverLeaved,
            widget,&DockWidget::onDockButtonLeaved);
//    qDebug() << dockWidgetButtons;
}

void DockWidgetToolBar::removeDockWidget(DockWidget *widget)
{
    QAction *action = dockWidgetButtons.value(widget);
    removeAction(action);
    dockWidgetButtons.remove(widget);
    delete action;
}
