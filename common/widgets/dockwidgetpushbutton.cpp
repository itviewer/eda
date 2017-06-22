#include "dockwidgetpushbutton.h"
#include <QStylePainter>
#include <QStyleOptionButton>
#include <QDebug>

DockWidgetPushButton::DockWidgetPushButton(const QString &text, Qt::Orientation orientation)
    : QPushButton(text, nullptr),
      orientation(orientation)
{
    setToolTip(text);

    int fw = fontMetrics().width(text)+12;

    fw = (fw < 15) ? 15 : fw;
    fw = (fw > 120) ? 121 : fw;

    if(orientation == Qt::Vertical) {
        setFixedSize(25, fw);
    }else{
        setFixedSize(fw, 25);
    }
}

DockWidgetPushButton::~DockWidgetPushButton()
{

}

void DockWidgetPushButton::enterEvent(QEvent *event)
{
    emit hoverEntered();
    QPushButton::enterEvent(event);
}

void DockWidgetPushButton::leaveEvent(QEvent *event)
{
    emit hoverLeaved();
    QPushButton::leaveEvent(event);
}

void DockWidgetPushButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QStylePainter painter(this);

    if(orientation = Qt::Vertical){
//        if(m_mirrored)
//        {
//            painter.rotate(-90);
//            painter.translate(-height(), 0);
//        }
//        else
//        {
            painter.rotate(90);
            painter.translate(0, -width());
//        }
    }

    painter.drawControl(QStyle::CE_PushButton, getStyleOption());
}

//void DockWidgetPushButton::resizeEvent(QResizeEvent *event)
//{

//}

QSize DockWidgetPushButton::sizeHint() const
{
    QSize size = QPushButton::sizeHint();
    if(orientation == Qt::Vertical) {
        size.transpose();
    }
    return size;
}

QStyleOptionButton DockWidgetPushButton::getStyleOption() const
{
    QStyleOptionButton opt;
    opt.initFrom(this);

    if(orientation == Qt::Vertical)
    {
        QSize size = opt.rect.size();
        size.transpose();
        opt.rect.setSize(size);
    }

    opt.features = QStyleOptionButton::None;

    if(isFlat()) {
        opt.features |= QStyleOptionButton::Flat;
    }
//    if(menu()) {
//        opt.features |= QStyleOptionButton::HasMenu;
//    }

    if(autoDefault() || isDefault()) {
        opt.features |= QStyleOptionButton::AutoDefaultButton;
    }

    if(isDefault()) {
        opt.features |= QStyleOptionButton::DefaultButton;
    }

//    if(isDown() || (menu() && menu()->isVisible())) {
//        opt.state |= QStyle::State_Sunken;
//    }

    if(isChecked()) {
        opt.state |= QStyle::State_On;
    }

    if(!isFlat() && !isDown()) {
        opt.state |= QStyle::State_Raised;
    }

    opt.text = text();
    opt.icon = icon();
    opt.iconSize = iconSize();
    return opt;
}

void DockWidgetPushButton::setText(const QString &text)
{
    int aw = (orientation == Qt::Horizontal) ? width() - 4 : height() - 4;

    QFontMetrics fm = fontMetrics();
    if(aw < fm.width(text))
    {
        QString str;

        // Need to cut the text
        for(int i = 0; i < text.size(); i++)
        {
            str += text.at(i);

            if(fm.width(str + ".......") > aw)
                break;
        }

        QPushButton::setText(str + "...");
    }
    else
    {
        QPushButton::setText(text);
    }
}
