#ifndef GLOBALSETTINGCOLORSCHEME_H
#define GLOBALSETTINGCOLORSCHEME_H

#include <QWidget>

namespace Ui {
    class GlobalSettingColorScheme;
}

class ColorSelector;

class GlobalSettingColorScheme : public QWidget
{
    Q_OBJECT

public:
    explicit GlobalSettingColorScheme(QWidget *parent = 0);
    ~GlobalSettingColorScheme();


protected:
    void showEvent(QShowEvent *event);

private slots:
    void createNewColorScheme();
    void onComboBoxColorSchemeChanged(const QString &schemeName);

    void onPushButtonSaveClicked();
    void onPushButtonDeleteClicked();

    void onPushButtonOKClicked();
    void onPushButtonApplyClicked();

private:
    Ui::GlobalSettingColorScheme *ui;
    QHash<QString,ColorSelector*> colorMap;

    const QVector<QString> colors =
    {
        "Background","Display","Selection","Drawing","Hierarchical",
        "Grid","Part","Pin","Power","Junction","NoConnect","Wire","Bus","Off-page",
        "PartReference","PartType","PinName","PinNumber","NetName","Text","Title"
    };

    bool askColorSchemeName(QString &newSchemeName);
    QHash<QString,QString> colorMapToColor();

};

#endif // GLOBALSETTINGCOLORSCHEME_H
