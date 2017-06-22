#include "settinggrid.h"
#include "ui_settinggrid.h"
#include "global.h"
#include "parteditor.h"
#include "partscene.h"

SettingGrid::SettingGrid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingGrid)
{
    ui->setupUi(this);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

    ui->comboBoxDesignGrid->addItems(gridSizes);
    ui->comboBoxDisplayGrid->addItems(gridSizes);

    // TODO 排除一打开就自动执行一下
    connect(ui->comboBoxDesignGrid,&QComboBox::currentTextChanged,this,[this](const QString &gridSize){
        ui->lineEditDesignGrid->setText(gridSize);
        designGridSize = gridSize.toInt() / milPerUnit;
    });

    connect(ui->comboBoxDisplayGrid,&QComboBox::currentTextChanged,this,[this](const QString &gridSize){
        ui->lineEditDisplayGrid->setText(gridSize);
        emit partEditor->currentScene()->displayGridSizeChanged();
        displayGridSize = gridSize.toInt() / milPerUnit;
    });
}

SettingGrid::~SettingGrid()
{
    delete ui;
}

void SettingGrid::showEvent(QShowEvent *event)
{
    const QString designGridSizeString = QString::number(designGridSize * milPerUnit);
    const QString displayGridSizeString = QString::number(displayGridSize * milPerUnit);

    ui->lineEditDesignGrid->setText(designGridSizeString);
    ui->lineEditDisplayGrid->setText(displayGridSizeString);

    ui->comboBoxDesignGrid->setCurrentText(designGridSizeString);
    ui->comboBoxDisplayGrid->setCurrentText(displayGridSizeString);

    QWidget::showEvent(event);
}
