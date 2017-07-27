#ifndef COLORSELECTOR_H
#define COLORSELECTOR_H

#include <QFrame>

class ColorSelector : public QFrame
{
public:
    ColorSelector(const QString &initial = "#ffffff",QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QString originColor() const;
    QString currentColor() const;
    void setCurrentColor(const QString &color);

    bool colorChanged() const;

protected:

    void mousePressEvent(QMouseEvent *event);
private:
    QString m_originColor;
    QString m_currentColor;
};

#endif // COLORSELECTOR_H
