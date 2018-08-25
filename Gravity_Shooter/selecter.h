#ifndef SELECTER_H
#define SELECTER_H

#include <QDialog>

namespace Ui {
class Selecter;
}

class Selecter : public QDialog
{
    Q_OBJECT

public:
    explicit Selecter(QWidget *parent = 0);
    ~Selecter();

    struct Data {
        int width;
        int height;
        int minCnt;
        int maxCnt;
        int playerCnt;
        double minDst;
    };

signals:
    void set(Data);

private slots:
    void onAccepted();

private:
    Ui::Selecter *ui;
};

#endif // SELECTER_H
