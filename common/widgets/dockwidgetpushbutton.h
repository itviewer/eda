#ifndef DOCKWIDGETPUSHBUTTON_H
#define DOCKWIDGETPUSHBUTTON_H

#include <QPushButton>
#include <QEvent>

class DockWidgetPushButton : public QPushButton
{
    Q_OBJECT

public:
    DockWidgetPushButton(const QString& text, Qt::Orientation orientation);
    ~DockWidgetPushButton();

signals:
    void hoverEntered();
    void hoverLeaved();
protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

    void paintEvent(QPaintEvent* event);
//    void resizeEvent(QResizeEvent* event) override;
    QSize sizeHint() const;
private:
    Qt::Orientation orientation;

    QStyleOptionButton getStyleOption() const;
    void setText(const QString& text);
};

#endif // DOCKWIDGETPUSHBUTTON_H
