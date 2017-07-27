#include "colorselector.h"
#include <QColorDialog>
#include <QDebug>

ColorSelector::ColorSelector(const QString &initial, QWidget *parent, Qt::WindowFlags f)
    :QFrame(parent,f),
      m_originColor(initial),
      m_currentColor(initial)
{
    setFixedSize(15,15);
    setStyleSheet(QString("background-color:%1;").arg(m_currentColor));
}

QString ColorSelector::originColor() const
{
    return m_originColor;
}

QString ColorSelector::currentColor() const
{
    return m_currentColor;
}

void ColorSelector::setCurrentColor(const QString &color)
{
    m_originColor = m_currentColor;
    m_currentColor = color;
    setStyleSheet(QString("background-color:%1;").arg(m_currentColor));
}

bool ColorSelector::colorChanged() const
{
    return m_originColor != m_currentColor;
}

void ColorSelector::mousePressEvent(QMouseEvent *event)
{
    const QColor color = QColorDialog::getColor(QColor(m_currentColor));
    if(color.isValid()){
        setCurrentColor(color.name());
    }
}
