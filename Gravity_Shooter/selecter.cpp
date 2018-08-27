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
    info.minPlanetCount = std::size_t(ui->minCntSpinBox->value());
    info.maxPlanetCount = std::size_t(ui->maxCntSpinBox->value());
    info.playerCount = std::size_t(ui->playerSpinBox->value());

    info.minDistance = ui->minDstSpinBox->value();

    info.minR = ui->minRadiusSpinBox->value();
    info.maxR = ui->maxRadiusSpinBox->value();
    info.minBetweenPercent = ui->minBetweenSpinBox->value();
    info.eps = ui->epsSpinBox->value();
    info.speed = ui->speedSpinBox->value();
    info.range = ui->rangeSpinBox->value();
    info.shipRadius = ui->shipRadiusSpinBox->value();
    info.speedAtBeginning = ui->speedAtBeginningSpinBox->value();
    info.bombDensity = ui->bombDensitySpinBox->value();


    set(info);
}
