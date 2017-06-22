#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QDockWidget>

class DockWidgetTitle;
class QMainWindow;

class DockWidget : public QDockWidget
{
    Q_OBJECT

public:
    DockWidget(const QString& title,QMainWindow *parent = nullptr);
    ~DockWidget();

    void setWindowTitle(const QString& title);
signals:
    void autoHideButtonClicked(bool autoHide);
public slots:
    void onDockButtonEntered();
    void onDockButtonLeaved();
protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
private:
    QMainWindow* mainWindow;
    DockWidgetTitle *titleBar;
    bool autoHide;
    bool shouldHide;

    void delayHide(int msec = 400);

};

#endif // DOCKWIDGET_H
