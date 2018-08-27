#include "widget.h"

#define maxTryCnt 25

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
    timer->stop();
    delete timer;
    delete stage;
    delete core;
}

void Widget::start(const Info &info)
{
    //qDebug("starting");

    timer->stop();

    size_t tryCnt = 0;
    while(core->init(info)!=0) {
        if (++tryCnt >= maxTryCnt) {
            qDebug("生成失败，条件过于苛刻！请重试或减少玩家/行星数量……或者重试。");
            return ;
        }

        qDebug("正在尝试生成……已尝试%d次。\n",tryCnt);
    }
    qDebug("生成成功！\n");
    current_id = info.playerCount-1;
    //qDebug("current id %u", current_id);

    last_point.clear();
    current_point.clear();
    last_point.resize(int(core->getInfo().playerCount));
    current_point.resize(int(core->getInfo().playerCount));

    stage_size.setHeight(info.height);
    stage_size.setWidth(info.width);
    resize(stage_size);

    delete stage;
    stage = new QPixmap(stage_size);
    stage->fill();
    repaint();

    //qDebug("end start");

    prepare();
}

void Widget::prepare()
{
    QPainter painter;
    painter.begin(stage);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setFont(QFont("Consolas", 20));

    set(painter);

    painter.setBrush(QColor("black"));
    for(auto i=core->getPlanets().begin(); i!=core->getPlanets().end(); ++i) {
        painter.drawEllipse(QPointF(i->x, i->y), i->radius, i->radius);
    }
    painter.setPen("red");
    painter.setBrush(QColor("red"));
    for(auto i=core->getShips().begin(); i!=core->getShips().end(); ++i) {
        painter.drawEllipse(QPointF(i->x, i->y), 5, 5);
    }
}

void Widget::fire(double deg, double power)
{
    size_t loopCount = 0;
    size_t new_id = current_id;
    do {
        (++new_id) %= core->getInfo().playerCount;
        if (++loopCount > core->getInfo().playerCount) {
            return ;
        }
    } while(!core->isAvailable(new_id));
    current_id = new_id;

    //qDebug("init");
    last_point.clear();
    current_point.clear();
    last_point.resize(int(core->getInfo().playerCount));
    current_point.resize(int(core->getInfo().playerCount));


    //qDebug("id is %d %f %f", current_id, deg, power);
    core->shoot(current_id, power, deg);
    //qDebug("shoot_ed");
    timer->start(10);
}

void Widget::set(QPainter &painter)
{
    painter.scale(1/(1+2*core->getInfo().range), 1/(1+2*core->getInfo().range));
    painter.translate(core->getInfo().width*core->getInfo().range, core->getInfo().height*core->getInfo().range);
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QRect(QPoint(), stage_size), *stage);

    set(painter);

    painter.setPen(QPen(/*core->getBomb().color*/QColor("green"), 1));
    painter.setBrush(QColor("green"));

    for(int i=0; i<int(core->getInfo().playerCount); ++i) {
        if(!current_point[i].isNull()) painter.drawEllipse(current_point[i], 5, 5);
    }

}

void Widget::turn_single(int id)
{
    if(core->getBombs()[size_t(id)].isCrashed) return ;
    current_point[id] = QPointF(core->getBombs()[size_t(id)].x, core->getBombs()[size_t(id)].y);

    QPainter painter;
    painter.begin(stage);
    painter.setPen(QPen(/*core->getBomb().color*/QColor("green"), 1));

    set(painter);
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
    for(int i=0; i<int(core->getInfo().playerCount); ++i) {
        //qDebug("start [%d]", i);
        turn_single(i);
        //qDebug("end [%d]", i);
    }
    repaint();
}
