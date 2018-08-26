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
    Info info = Info();
    info.width = ui->widthSpinBox->value();
    info.height = ui->heightSpinBox->value();
    info.minPlanetCount = ui->minCntSpinBox->value();
    info.maxPlanetCount = ui->maxCntSpinBox->value();
    info.playerCount = ui->playerSpinBox->value();
    info.minDistance = ui->minDstSpinBox->value();
    set(info);
}
