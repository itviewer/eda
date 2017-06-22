#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <QTreeWidget>

class PCBScene;

class Navigator : public QTreeWidget
{
    Q_OBJECT

public:
    Navigator(QWidget *parent = nullptr);
    ~Navigator();

    QSize sizeHint() const;
    void createNavigator();

public slots:
private:
};

#endif // NAVIGATOR_H
