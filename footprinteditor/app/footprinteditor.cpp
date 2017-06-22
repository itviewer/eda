#include "footprinteditor.h"
#include "ui_footprinteditor.h"

FootprintEditor::FootprintEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FootprintEditor)
{
    ui->setupUi(this);
}

FootprintEditor::~FootprintEditor()
{
    delete ui;
}
