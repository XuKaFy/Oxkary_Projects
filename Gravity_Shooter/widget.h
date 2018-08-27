#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QVector>
#include <QTimer>
#include <QPixmap>

#include "header/object.h"

class GravityShooterCore;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void start(const Info &info);
    void fire(double deg, double power);

protected:
    void paintEvent(QPaintEvent *);

private:
    void set(QPainter &painter);

    void prepare();
    void turn_single(int id);

    QPixmap *stage;
    QTimer *timer;
    QVector<QPointF> last_point, current_point;
    GravityShooterCore *core;
    QSize stage_size;
    size_t current_id;

private slots:
    void turn();
};

#endif // PLAYER_H
