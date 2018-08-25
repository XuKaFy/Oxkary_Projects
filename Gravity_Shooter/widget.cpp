#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(turn()));

    core = new GravityShooter();
}

Widget::~Widget()
{
    planet.clear();
    ship.clear();
}

void Widget::start(int player_count, int min_planet, int max_planet, double min_distance, int height, int width)
{
    core->init(min_planet, max_planet, player_count, min_distance, height, width, std::vector<int>(player_count));
    id = player_count;
    current_id = id-1;
    stage_size.setHeight(height);
    stage_size.setWidth(width);
    stage = new QPixmap(stage_size);
    stage->fill();
    resize(stage_size);
    prepare();
}

void Widget::prepare()
{
    planet = QVector<Planet>::fromStdVector(core->shooter.getPlanets());
    ship = QVector<Ship>::fromStdVector(core->shooter.getShips());

    QPainter painter;
    painter.begin(stage);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setFont(QFont("Consolas", 20));

    painter.scale(0.5, 0.5);
    painter.translate(stage_size.width()/2, stage_size.height()/2);

    painter.setBrush(QColor("black"));
    for(auto i=planet.begin(); i!=planet.end(); ++i) {
        painter.drawEllipse(QPointF(i->x, i->y), i->r, i->r);
    }
    painter.setPen("red");
    painter.setBrush(QColor("red"));
    for(auto i=ship.begin(); i!=ship.end(); ++i) {
        painter.drawEllipse(QPointF(i->x, i->y), 10, 10);
    }
}

void Widget::fire(double deg, double power)
{
    (++current_id) %= id;

    last_point.setX(0);
    last_point.setY(0);

    //qDebug("id is %d %f %f", current_id, deg, power);
    core->shoot(current_id, power, deg);
    timer->start(10);
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QRect(QPoint(), stage_size), *stage);
}

void Widget::turn()
{
    core->calculate();
    QPointF current_point(core->getBomb().x, core->getBomb().y);

    QPainter painter;
    painter.begin(stage);
    painter.setPen(QPen(/*core->getBomb().color*/QColor("green"), 2));

    painter.scale(0.5, 0.5);
    painter.translate(stage_size.width()/2, stage_size.height()/2);

    if(!last_point.isNull()) {
        painter.drawLine(last_point, current_point);
    }
    last_point = current_point;

    repaint();
    if(core->getBomb().isCrashed) {
        timer->stop();
    }
}
