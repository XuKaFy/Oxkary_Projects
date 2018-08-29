#ifndef OBJECT_H
#define OBJECT_H

#include <bits/stdc++.h>
#include <QFile>
#include <QDebug>
#include <QSettings>
#include <QtMath>
#include <QTime>
#include "definition.h"

typedef double real;

struct Object
{
    Object(real x = 0, real y = 0, real radius = 1, bool movable = true)
        : x(x), y(y), radius(radius), movable(movable) { }

    real x, y, radius;
    bool movable;
};

struct Planet : public Object
{
    Planet(real x = 0, real y = 0, real radius = 1, bool movable = true, real density = 0.01, real vx = 0, real vy = 0)
        : Object(x, y, radius, movable), density(density), vx(vx), vy(vy) { }

    real getMass() const {
//        qDebug("r:%lf,den:%lf",radius,density);
        return SQR(radius) * density;
    }

    real density;
    real vx, vy;
};

struct Bomb : public Planet
{
    explicit Bomb(real x = 0, real y = 0, real radius = 1,
                  bool movable = true, real density = 1, real vx = 0, real vy = 0, int id = -1 ,bool isCrashed = true)

        : Planet(x, y, radius, movable, density, vx, vy), isCrashed(isCrashed), id(id) { }

    void getNext(real ax, real ay) {
        x += vx;
        y += vy;
        vx += ax;
        vy += ay;
        isCrashed = false;
    }

    bool isCrashed;

    int flyFrames;
    int id;
    void crash() {
        isCrashed=true;
        flyFrames=0;
        x=static_cast<real>(inf);
        y=static_cast<real>(inf);
        vx=0;
        vy=0;
    }

};

struct Ship : public Object
{
    Ship(real x = 0, real y = 0, real radius = 1, bool movable = true)
        : Object(x, y, radius, movable), isFailed(false) { }

    bool isFailed;
};

#define OBJECT_ARGUMENT_TABLE \
    ENTRY(minPlanetCount, uint) \
    ENTRY(maxPlanetCount, uint) \
    ENTRY(playerCount, uint) \
    ENTRY(minDistance, real) \
    ENTRY(width, int) \
    ENTRY(height, int) \
    ENTRY(minBetweenPercent, real) \
    ENTRY(eps, real) \
    ENTRY(speed, real) \
    ENTRY(range, real) \
    ENTRY(shipRadius, real) \
    ENTRY(speedAtBeginning, real) \
    ENTRY(bombDensity, real) \
    ENTRY(planetDensity, real) \
    ENTRY(allowMoreShootsWhenPVP, bool) \
    /*ENTRY(loadFrames, int)*/ \
    ENTRY(minR, real) \
    ENTRY(maxR, real)

struct Info {

    Info () {
        QSettings *settings = new QSettings(":/default.ini", QSettings::IniFormat);
#define ENTRY(x, T) x = qvariant_cast<T>(settings->value("/settings/"#x));
        OBJECT_ARGUMENT_TABLE
#undef ENTRY
        delete settings;
    }
#define ENTRY(a, b) b a;
    OBJECT_ARGUMENT_TABLE
#undef ENTRY
};

#define Vector std::vector

class GravityShooterCore
{
public:
    static real randReal01() {
        return qrand() / real(RAND_MAX);
    }

    static real randomReal(real Min, real Max) {
        return randReal01()*(Max-Min)+Min;
    }

    static int randomInt(int Min, int Max) {
        return (rand() % (Max-Min+1))+ Min;
    }

    static real distance(real x1, real y1, real x2, real y2) {
        return sqrt(SQR(x1-x2)+SQR(y1-y2));
    }

    static bool isBetween(real leftRange, real rightRange, real x) {
        return leftRange <=x && x <= rightRange;
    }

    bool isAvailable(uint id) {
        if (id >= ships.size() || id >= bombs.size())
            return false;
        if (flyingBombCounts > 0 && info.allowMoreShootsWhenPVP == false)
            return false;
        if (!bombs[id].isCrashed)
            return false;
        return true;
    }

    void crashBomb(Bomb &bomb) {
        bomb.crash();
        --flyingBombCounts;
    }

    GravityShooterCore(const Info &info = Info())
        : info(info), flyingBombCounts(0) { }

    Info getInfo() const {
        return info;
    }

    int init(const Info &info_new) {
        int loopCnt = 0;
        info = info_new;
        planets.clear();
        ships.clear();
        bombs.clear();
        flyingBombCounts = 0;
        qsrand(static_cast<uint>(QTime::currentTime().msec()));
        qDebug("playercount: %d", info.playerCount);
        for (uint i=0; i<info.playerCount; ++i) {
            bool access=true;
            real x, y;
            do {
                x = randReal01() * info.width;
                y = randReal01() * info.height;
                access=true;
                for (uint j=0; j<i; ++j) {
                    if (distance(ships[j].x, ships[j].y, x, y) < info.minDistance)
                        access = false;
                }
                if (++loopCnt >= maxLoopCnt)
                    return -1;
            } while(!access);
            ships.push_back(Ship(x, y, info.shipRadius));
        }

        loopCnt = 0;

        uint planetCnt = uint(randomInt(int(info.minPlanetCount), int(info.maxPlanetCount)));

        for (uint i=0;i<planetCnt;i++) {
            real x, y, nowMaxR;
            bool access=true;
            uint num = ships.size();
            do {
                access = true;
                x = randReal01() * info.width;
                y = randReal01() * info.height;
                nowMaxR = static_cast<real>(inf);
                for (uint j=0; j<num; ++j) {
                    nowMaxR = qMin(nowMaxR, distance(ships[j].x, ships[j].y, x, y)-ships[j].radius);
                }
                for (uint j=0; j<i; ++j) {
                    nowMaxR = qMin(nowMaxR, distance(planets[j].x, planets[j].y, x, y) - planets[j].radius);
                }
                if (nowMaxR /  (info.minBetweenPercent + 1)<info.minR) access=false;
                if (++loopCnt >= maxLoopCnt)
                    return -1;
            } while(!access);
            real r = randomReal(info.minR, qMin(info.maxR, nowMaxR /  (info.minBetweenPercent + 1)));
            planets.push_back(Planet(x, y, r, false, info.planetDensity, 0 ,0));
        }

        bombs.resize(info.playerCount);
        for(uint i=0; i<info.playerCount; ++i) {//开局炮弹放在无穷远处
            bombs[i].x = static_cast<real>(inf);
            bombs[i].y = static_cast<real>(inf);
        }
        return 0;
    }

    int calculate(uint id)
    {
        Bomb &bomb=this->bombs[id];
        if (bomb.isCrashed || bomb.id==-1) return -2;
        uint planetsCnt = planets.size();
        real ax = 0, ay = 0;
        for (uint i=0; i<planetsCnt; ++i) {
            Planet now = planets[i];
            real s = distance(bomb.x, bomb.y, now.x, now.y);
            ax += (now.getMass() / (SQR(s) * bomb.getMass())) * ((now.x-bomb.x)/s) * info.speed;
            ay += (now.getMass() / (SQR(s) * bomb.getMass())) * ((now.y-bomb.y)/s) * info.speed;

        }

        if (bomb.x < -info.width*info.range || bomb.y<-info.height*info.range || bomb.x>info.width+info.width*info.range || bomb.y>info.height+info.height*info.range) {
            crashBomb(bomb);
            //puts("-1");
            return -1;
        }
        for (uint i=0;i<planetsCnt;i++) {
            Planet now = planets[i];
            real s = distance(bomb.x, bomb.y, now.x, now.y);
            if (qFabs(s) < now.radius) {
                crashBomb(bomb);

                //puts("-1");
                return -1;
            }
        }
        uint shipsCnt = ships.size();
        for (uint i=0; i<shipsCnt; ++i) {
            Ship &now = ships[i];
            real s = distance(bomb.x, bomb.y, now.x, now.y);
            if (qFabs(s)<now.radius && !now.isFailed) {
                now.isFailed = true;
                crashBomb(bomb);
                return int(i);
            }
        }
        bomb.getNext(ax*info.speed, ay*info.speed);
        return 0;
    }

    Vector <int> multiCalculate()
    {
        Vector <int> result;
        uint bombsNum=bombs.size();
        for (uint i=0;i<bombsNum;i++) {
           result.push_back(calculate(i));
        }
        return result;
    }

    int shoot(uint id, real power, real deg)
    {
        if (flyingBombCounts > 0 && info.allowMoreShootsWhenPVP == false)
            return -1;
        ++flyingBombCounts;
        Bomb &bomb=this->bombs[id];
        real Sin = qSin(deg), Cos = qCos(deg);
        Ship now = ships[id];
        if (!bomb.isCrashed)
            return -2;
        if (now.isFailed)
            return -3;
        bomb = Bomb(now.x+((now.radius+info.eps)*Sin)+info.eps, now.y+((now.radius+info.eps)*Cos), info.shipRadius, true, info.bombDensity, info.speed*Sin*power*info.speedAtBeginning, info.speed*Cos*power*info.speedAtBeginning, static_cast<int>(id), false);
        return 0;
    }

    const Vector<Planet> &getPlanets() const
    {
        return planets;
    }

    const Vector<Ship> &getShips() const
    {
        return ships;
    }

    const Vector<Bomb> &getBombs() const
    {
        return bombs;
    }

private:
    Info info;
    Vector<Planet> planets;
    Vector<Ship> ships;
    Vector<Bomb> bombs;
    int flyingBombCounts;
};

#endif // OBJECT_H
