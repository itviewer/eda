#ifndef SETTING_H
#define SETTING_H

#include <QObject>

class Setting : public QObject
{
    Q_OBJECT
public:
    explicit Setting(QObject *parent = 0);

    inline void init();
    inline void initUnitsRatio();
signals:

//public slots:
private slots:
    void postInit();
private:
};

#endif // SETTING_H
