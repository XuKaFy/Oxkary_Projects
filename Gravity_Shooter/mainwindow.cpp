#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    resize(600, 600);
    setFont(QFont("Consolas", 9));

    view = new Widget(this);
    view->start(2, 5, 15, 10, 600, 600);

    power_spinbox = new QDoubleSpinBox(this);
    power_spinbox->setGeometry(40, 500, 200, 20);
    power_spinbox->setMaximum(1);
    power_spinbox->setMinimum(0);
    power_spinbox->setValue(0.5);
    deg_spinbox = new QDoubleSpinBox(this);
    deg_spinbox->setGeometry(40, 530, 200, 20);
    deg_spinbox->setMaximum(M_PI*2);
    deg_spinbox->setMinimum(0);
    deg_spinbox->setValue(M_PI);

    fire_button = new QPushButton(QStringLiteral("F"), this);
    fire_button->setGeometry(300, 500, 30, 30);
    connect(fire_button, SIGNAL(clicked()), this, SLOT(fire()));

    selecter = new Selecter();
    connect(selecter, SIGNAL(set(Data)), this, SLOT(onSet(Data)));

    set_button = new QPushButton(QStringLiteral("S"), this);
    set_button->setGeometry(350, 500, 30, 30);
    connect(set_button, SIGNAL(clicked()), selecter, SLOT(open()));
}

MainWindow::~MainWindow()
{
    delete selecter;
}

void MainWindow::onSet(const Data &d)
{
    view->start(d.playerCnt,
                d.minCnt,
                d.maxCnt,
                d.minDst,
                d.height,
                d.width);
}

void MainWindow::fire()
{
    view->fire(deg_spinbox->value(), power_spinbox->value());
}
