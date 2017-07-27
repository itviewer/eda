#ifndef SETTINGIO_H
#define SETTINGIO_H

#include <QObject>

class SettingIO : public QObject
{
    Q_OBJECT
public:
    explicit SettingIO(QObject *parent = nullptr);

    bool saveSchSetting();
signals:

//public slots:
private slots:

private:
    QString schSettingFile;

    void initEnvironment();
    void initSetting();

    void generateDefaultSchSetting();
};

#endif // SETTINGIO_H
