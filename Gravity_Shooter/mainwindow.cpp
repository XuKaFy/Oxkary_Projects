#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setFont(QFont("Consolas", 9));

    view = new Widget(this);
    info = Info();
    resize(info.width, info.height);
    view->start(info);

    power_spinbox = new QDoubleSpinBox();
    //power_spinbox->setGeometry(40, 500, 200, 20);
    power_spinbox->setMaximum(1);
    power_spinbox->setMinimum(0);
    power_spinbox->setValue(0.5);
    deg_spinbox = new QDoubleSpinBox();
    //deg_spinbox->setGeometry(40, 530, 200, 20);
    deg_spinbox->setMaximum(M_PI*2);
    deg_spinbox->setMinimum(0);
    deg_spinbox->setValue(M_PI);

    fire_button = new QPushButton(QStringLiteral("F"));
    //fire_button->setGeometry(300, 500, 30, 30);
    connect(fire_button, SIGNAL(clicked()), this, SLOT(fire()));

    selecter = new Selecter();
    connect(selecter, SIGNAL(set(Info)), this, SLOT(onSet(Info)));

    set_button = new QPushButton(QStringLiteral("S"));
    //set_button->setGeometry(350, 500, 30, 30);
    connect(set_button, SIGNAL(clicked()), selecter, SLOT(open()));

    QToolBar *toolBar = addToolBar(QStringLiteral(""));
    toolBar->addWidget(power_spinbox);
    toolBar->addWidget(deg_spinbox);
    toolBar->addWidget(fire_button);
    toolBar->addWidget(set_button);
}

MainWindow::~MainWindow()
{
    delete selecter;
}

void MainWindow::onSet(const Info &d)
{
    view->start(d);
}

void MainWindow::fire()
{
    view->fire(deg_spinbox->value(), power_spinbox->value());
}
