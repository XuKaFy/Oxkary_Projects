#include "selecter.h"
#include "ui_selecter.h"

Selecter::Selecter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Selecter)
{
    setFont(QFont("Consolas", 9));
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(onAccepted()));
}

Selecter::~Selecter()
{
    delete ui;
}

void Selecter::onAccepted()
{
    set(Data{
            ui->widthSpinBox->value(),
            ui->heightSpinBox->value(),
            ui->minCntSpinBox->value(),
            ui->maxCntSpinBox->value(),
            ui->planetSpinBox->value(),
            ui->minDstSpinBox->value()
        });
}
