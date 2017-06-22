#include "dockwidgettitle.h"
#include <QtWidgets>

static const QString autoHideDisabledStyle =
R"(QPushButton
{
    border: 0px;
    width: 15px; height: 15px;
    image: url(":/dock/pin_dockwidget_normal.png");
}
QPushButton:hover {
    image: url(":/dock/pin_dockwidget_hover.png");
}
QPushButton:pressed:hover {
    image: url(":/dock/pin_dockwidget_pressed.png");
})";

static const QString autoHideEnabledStyle =
R"(QPushButton
{
    border: 0px;
    width: 15px; height: 15px;
    image: url(":/dock/unpin_dockwidget_normal.png");
}
QPushButton:hover {
    image: url(":/dock/unpin_dockwidget_hover.png");
}
QPushButton:pressed:hover {
    image: url(":/dock/unpin_dockwidget_pressed.png");
})";

static const QString menuButtonStyle =
R"(QPushButton
{
    border: 0px;
    width: 15px; height: 15px;
    image: url(":/dock/menu_dockwidget_normal.png");
}
QPushButton:hover {
    image: url(":/dock/menu_dockwidget_hover.png");
}
QPushButton:pressed:hover {
    image: url(":/dock/menu_dockwidget_pressed.png");
})";


static const QString closeButtonStyle =
R"(QPushButton
{
    border: 0px;
    width: 15px; height: 15px;
    image: url(":/dock/close_dockwidget_normal.png");
}
QPushButton:hover {
    image: url(":/dock/close_dockwidget_hover.png");
}
QPushButton:pressed:hover {
    image: url(":/dock/close_dockwidget_pressed.png");
})";

DockWidgetTitle::DockWidgetTitle(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout();
    layout->setContentsMargins(3, 2, 3, 2);
    layout->setSpacing(1);

    labeltTitle = new QLabel();
    layout->addWidget(labeltTitle);

    layout->addStretch(1);

//    popMenuButton = new QPushButton();
//    popMenuButton->setStyleSheet(menuButtonStyle);
//    popMenuButton->setToolTip(tr("Menu"));
//    layout->addWidget(popMenuButton);

    autoHideButton = new QPushButton();
    autoHideButton->setStyleSheet(autoHideDisabledStyle);
    autoHideButton->setToolTip(tr("Auto Hide"));
    autoHide = false;
    layout->addWidget(autoHideButton);

    closeButton = new QPushButton();
    closeButton->setStyleSheet(closeButtonStyle);
    closeButton->setToolTip(tr("Close"));
    layout->addWidget(closeButton);

    setLayout(layout);

    connect(autoHideButton, &QPushButton::clicked, this,[=](){
        autoHide = !autoHide;
        if(autoHide) {
            autoHideButton->setStyleSheet(autoHideEnabledStyle);
        }
        else {
            autoHideButton->setStyleSheet(autoHideDisabledStyle);
        }
        emit autoHideButtonClicked(autoHide);
    });
    connect(closeButton, &QPushButton::clicked, this, &DockWidgetTitle::closeButtonClicked);
}

DockWidgetTitle::~DockWidgetTitle()
{

}

QString DockWidgetTitle::getTitle() const
{
    return labeltTitle->text();
}

void DockWidgetTitle::setTitle(const QString &text)
{
    labeltTitle->setText(text);
}
