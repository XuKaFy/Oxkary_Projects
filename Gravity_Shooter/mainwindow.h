#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QLabel>
#include <QToolBar>

#include "widget.h"
#include "selecter.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSet(const Info &d);
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
    Info info;
};

#endif // MAINWINDOW_H
