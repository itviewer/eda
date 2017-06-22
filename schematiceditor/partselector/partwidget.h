#ifndef PARTWIDGET_H
#define PARTWIDGET_H

#include <QGraphicsWidget>

class PartWidget : public QGraphicsWidget
{
public:
    PartWidget(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
};

#endif // PARTWIDGET_H
