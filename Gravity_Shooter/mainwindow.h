#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QLabel>
#include "widget.h"
#include "selecter.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    typedef Selecter::Data Data;

private slots:
    void onSet(const Data &d);
    void fire();

private:
    Widget *view;
    QLabel *name_label;
    QDoubleSpinBox *power_spinbox;
    QDoubleSpinBox *deg_spinbox;
    QPushButton *fire_button;
    QPushButton *set_button;
    Selecter *selecter;

    int id;
};

#endif // MAINWINDOW_H
