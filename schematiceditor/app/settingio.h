#ifndef SETTINGIO_H
#define SETTINGIO_H

#include <QObject>

class SettingIO : public QObject
{
    Q_OBJECT
public:
    explicit SettingIO(QObject *parent = nullptr);

signals:

//public slots:
private slots:

private:
    void initEnvironment();
    void initSetting();

    void generateDefaultSchSetting(const QString &filename);
};

#endif // SETTINGIO_H
