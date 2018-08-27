#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(turn()));

    core = new GravityShooterCore();

    stage = nullptr;
}

Widget::~Widget()
{
    planet.clear();
    ship.clear();

    timer->stop();
    delete timer;
    delete stage;
    delete core;
}

void Widget::start(const Info &info)
{
    //qDebug("starting");
    timer->stop();

    core->init(info);
    id = info.playerCount;

    //qDebug("resize %d", int(id));
    last_point.resize(int(id));
    current_point.resize(int(id));

    current_id = id-1;
    //qDebug("current id %u", current_id);
    stage_size.setHeight(info.height);
    stage_size.setWidth(info.width);
    delete stage;
    stage = new QPixmap(stage_size);
    stage->fill();
    repaint();
    resize(stage_size);

    //qDebug("end start");

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

    //qDebug("init");
    for(int i=0; i<int(id); ++i) {
        last_point[i].setX(0);
        last_point[i].setY(0);
        current_point[i].setX(0);
        current_point[i].setY(0);
    }

    //qDebug("id is %d %f %f", current_id, deg, power);
    core->shoot(current_id, power, deg);
    //qDebug("shoot_ed");
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

    for(int i=0; i<int(id); ++i) {
        if(!current_point[i].isNull()) painter.drawEllipse(current_point[i], 5, 5);
    }
}

void Widget::turn_single(int id)
{
    if(core->getBombs()[size_t(id)].isCrashed) return ;
    current_point[id] = QPointF(core->getBombs()[size_t(id)].x, core->getBombs()[size_t(id)].y);

    QPainter painter;
    painter.begin(stage);
    painter.setPen(QPen(/*core->getBomb().color*/QColor("green"), 2));

    painter.scale(0.5, 0.5);
    painter.translate(stage_size.width()/2, stage_size.height()/2);

    if(!last_point[(id)].isNull()) {
        painter.drawLine(last_point[id], current_point[id]);
    }
    last_point[id] = current_point[id];

    /*if(core->getBomb(id).isCrashed) {
        timer->stop();
    }*/
}

void Widget::turn()
{
    //qDebug("come turn");
    core->multiCalculate();
    for(int i=0; i<int(id); ++i) {
        //qDebug("start [%d]", i);
        turn_single(i);
        //qDebug("end [%d]", i);
    }
    repaint();
}
