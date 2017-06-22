#ifndef DOCKWIDGETTITLE_H
#define DOCKWIDGETTITLE_H

#include <QWidget>

class QPushButton;
class QLabel;

class DockWidgetTitle : public QWidget
{
    Q_OBJECT
public:
    explicit DockWidgetTitle(QWidget *parent = 0);
    ~DockWidgetTitle();

    QString getTitle() const;
    void setTitle(const QString& text);

signals:
    void autoHideButtonClicked(bool autoHide);
    void closeButtonClicked();
public slots:
private:
    QPushButton* popMenuButton;
    QPushButton* autoHideButton;
    QPushButton* closeButton;

    bool autoHide;

    QLabel* labeltTitle;
};

#endif // DOCKWIDGETTITLE_H
