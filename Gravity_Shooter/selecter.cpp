#include "selecter.h"
#include "ui_selecter.h"

Selecter::Selecter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Selecter)
{
    setFont(QFont("Consolas", 9));
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(onAccepted()));

    Info info = Info();
#define ENTRY(a, b) ui->a##Geter->setValue(info.a);
    OBJECT_ARGUMENT_TABLE
#undef ENTRY
}

Selecter::~Selecter()
{
    delete ui;
}

void Selecter::onAccepted()
{
    Info info = Info();
#define ENTRY(a, b) info.a = ui->a##Geter->value();
    OBJECT_ARGUMENT_TABLE
#undef ENTRY
    set(info);
}
