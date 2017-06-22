#ifndef PARTIO_H
#define PARTIO_H

#include <QObject>
#include "global.h"

class PartIO : public QObject
{
    Q_OBJECT
public:
    explicit PartIO(QObject *parent = nullptr);

signals:

public slots:
};

#endif // PARTIO_H
