#ifndef SELECTER_H
#define SELECTER_H

#include <QDialog>

#include "header/object.h"

namespace Ui {
class Selecter;
}

class Selecter : public QDialog
{
    Q_OBJECT

public:
    explicit Selecter(QWidget *parent = 0);
    ~Selecter();

signals:
    void set(Info);

private slots:
    void onAccepted();

private:
    Ui::Selecter *ui;
};

#endif // SELECTER_H
