#include "dockwidget.h"
#include "dockwidgettitle.h"
#include "dockwidgettoolbar.h"
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QDebug>
#include "common.h"
#include <QEvent>
#include <QTimer>

DockWidget::DockWidget(const QString& title, QMainWindow *parent)
    :QDockWidget(parent),
      mainWindow(parent),
      autoHide(false),
      shouldHide(true)
{
    titleBar = new DockWidgetTitle();
    setTitleBarWidget(titleBar);
    setWindowTitle(title);

    connect(titleBar, &DockWidgetTitle::autoHideButtonClicked, this,[=](bool state){
        autoHide = state;
        emit autoHideButtonClicked(state);
    });
    connect(titleBar, &DockWidgetTitle::closeButtonClicked, this,[=](){
        hide();
    });


    connect(this,&DockWidget::topLevelChanged,this,[=](bool floating){
        // 默认在使用自定义title且浮点时不会添加边框 修改后当浮动时手动隐藏自定义标题
        floating ? titleBar->hide() : titleBar->show();
    });
}

DockWidget::~DockWidget()
{

}

void DockWidget::setWindowTitle(const QString& title)
{
    titleBar->setTitle(title);
    QDockWidget::setWindowTitle(title);
}

void DockWidget::onDockButtonEntered()
{
    if(isVisible()){
       shouldHide = false;
    }else{
       shouldHide = true;
       show();
    }
}

void DockWidget::onDockButtonLeaved()
{
    shouldHide = true;
    delayHide();
}

void DockWidget::enterEvent(QEvent *event)
{
    if(autoHide){
        shouldHide = false;
    }
    QDockWidget::enterEvent(event);
}

void DockWidget::leaveEvent(QEvent *event)
{
    if(autoHide){
        shouldHide = true;
        delayHide(200);
    }
    QDockWidget::leaveEvent(event);
}

void DockWidget::delayHide(int msec)
{
    QTimer::singleShot(msec, this,[=](){
        if(shouldHide){
            hide();
//            QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
//            animation->setDuration(400);
//            animation->setStartValue(geometry());
//            animation->setEndValue(QRect(-200,y(),width(),height()));
//            animation->start();
//            connect(animation,&QPropertyAnimation::finished,this,&DockWidget::hide);
        }
    });
}
