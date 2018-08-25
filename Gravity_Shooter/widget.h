#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QVector>
#include <QTimer>
#include <QPixmap>

#include "gravity.h"

class GravityShooter;
class Planet;
class Ship;
class Bomb;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void start(int player_count, int min_planet, int max_planet, double min_distance, int height, int width);
    void fire(double deg, double power);

protected:
    void paintEvent(QPaintEvent *);

private:
    void prepare();

    QVector<Planet> planet;
    QVector<Ship> ship;
    QPixmap *stage;
    QTimer *timer;
    QPointF last_point;
    GravityShooter *core;
    QSize stage_size;
    int id, current_id;

private slots:
    void turn();
};

#endif // PLAYER_H
