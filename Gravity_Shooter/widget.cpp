#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(turn()));

    core = new GravityShooterCore();
}

Widget::~Widget()
{
    planet.clear();
    ship.clear();
}

void Widget::start(const Info &info)
{
    timer->stop();

    core->init(info);
    id = info.playerCount;
    current_id = id-1;
    stage_size.setHeight(info.height);
    stage_size.setWidth(info.width);
    stage = new QPixmap(stage_size);
    stage->fill();
    repaint();
    resize(stage_size);
    prepare();
}

void Widget::prepare()
{
    planet = QVector<Planet>::fromStdVector(core->getPlanets());
    ship = QVector<Ship>::fromStdVector(core->getShips());

    QPainter painter;
    painter.begin(stage);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setFont(QFont("Consolas", 20));

    painter.scale(0.5, 0.5);
    painter.translate(stage_size.width()/2, stage_size.height()/2);

    painter.setBrush(QColor("black"));
    for(auto i=planet.begin(); i!=planet.end(); ++i) {
        painter.drawEllipse(QPointF(i->x, i->y), i->radius, i->radius);
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
    current_point.setX(0);
    current_point.setY(0);

    //qDebug("id is %d %f %f", current_id, deg, power);
    core->shoot(current_id, power, deg);
    timer->start(10);
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QRect(QPoint(), stage_size), *stage);

    painter.scale(0.5, 0.5);
    painter.translate(stage_size.width()/2, stage_size.height()/2);
    painter.setPen(QPen(/*core->getBomb().color*/QColor("green"), 2));
    painter.setBrush(QColor("green"));

    if(!current_point.isNull()) painter.drawEllipse(current_point, 5, 5);
}

void Widget::turn()
{
    core->calculate();
    current_point = QPointF(core->getBomb().x, core->getBomb().y);

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
