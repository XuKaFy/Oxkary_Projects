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
class Planet;
class Ship;
class Bomb;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void start(const Info &info);
    void fire(double deg, double power);

protected:
    void paintEvent(QPaintEvent *);

private:
    void prepare();

    QVector<Planet> planet;
    QVector<Ship> ship;
    QPixmap *stage;
    QTimer *timer;
    QPointF last_point, current_point;
    GravityShooterCore *core;
    QSize stage_size;
    int id, current_id;

private slots:
    void turn();
};

#endif // PLAYER_H
