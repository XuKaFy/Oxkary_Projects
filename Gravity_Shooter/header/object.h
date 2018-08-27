#ifndef OBJECT_H
#define OBJECT_H

#include <cstdlib>
#include <ctime>
#include <vector>

#include <algorithm>
#include <iostream>


typedef double real;

#define SQR(n) ((n)*(n))
#define inf 999999999

struct Object
{
    Object(real x = 0, real y = 0, real radius = 1, bool movable = true)
        : x(x), y(y), radius(radius), movable(movable) { }

    real x, y, radius;
    bool movable;
};

struct Planet : public Object
{
    Planet(real x = 0, real y = 0, real radius = 1, bool movable = true, real density = 1, real vx = 0, real vy = 0)
        : Object(x, y, radius, movable), density(density), vx(vx), vy(vy) { }

    real getMass() const {
        return SQR(radius) * density;
    }

    real density;
    real vx, vy;
};

struct Bomb : public Planet
{
    explicit Bomb(real x = 0, real y = 0, real radius = 1, bool movable = true, real density = 1, real vx = 0, real vy = 0, int id = 0)

        : Planet(x, y, radius, movable, density, vx, vy), isCrashed(false), id(id) { }

    void getNext(real ax, real ay) {
        x += vx;
        y += vy;
        vx += ax;
        vy += ay;
    }

    bool isCrashed;


    int flyFrames;
    int id;
    void crash() {
        isCrashed=true;
        flyFrames=0;
    }

};

struct Ship : public Object
{
    Ship(real x = 0, real y = 0, real radius = 1, bool movable = true)
        : Object(x, y, radius, movable), isFailed(false) { }

    bool isFailed;
};

struct Info {
    Info() {
        minPlanetCount = 5;
        maxPlanetCount = 10;
        playerCount = 2;
        minDistance = 10.0;
        width = 600;
        height = 600;

        minR = 2.0;
        maxR = 30.0;
        minBetweenPercent = 0.5;
        eps = 1;

        speed = 1;
        range = 0.5;
        shipRadius = 10;
        speedAtBeginning = 2;
        bombDensity = 0.2;
    }

    size_t minPlanetCount;
    size_t maxPlanetCount;
    size_t playerCount;

    real minDistance;
    int width;
    int height;

    real minR;
    real maxR;
    real minBetweenPercent;
    real eps;

    real speed;
    real range;
    real shipRadius;
    real speedAtBeginning;
    real bombDensity;
};

#define Vector std::vector
typedef std::size_t size_t;


class GravityShooterCore
{
public:
    static double randDouble01() {
        return rand() / double(RAND_MAX);
    }

    static double randomDouble(double Min, double Max) {
        return randDouble01()*(Max-Min)+Min;
    }

    static int randomInt(int Min,int Max) {
        return (rand() % (Max-Min+1))+ Min;

    }

    static double distance(double x1, double y1, double x2, double y2) {
        return sqrt(SQR(x1-x2)+SQR(y1-y2));
    }

    GravityShooterCore(const Info &info = Info())
        : info(info) { }

    Info getInfo() const {
        return info;
    }

    void init(const Info &info_new) {
        info = info_new;
        planets.clear();
        ships.clear();
        bombs.clear();

        srand(time(0));
        for (size_t i=0; i<info.playerCount; ++i) {
            bool access=true;
            double x, y;
            do {
                x = randDouble01() * info.width;
                y = randDouble01() * info.height;
                access=true;
                for (size_t j=0; j<i; ++j) {
                    if (distance(ships[j].x, ships[j].y, x, y) < info.minDistance)
                        access = false;
                }
            } while(!access);
            ships.push_back(Ship(x, y, info.shipRadius));
        }

        size_t planetCnt = size_t(randomInt(int(info.minPlanetCount), int(info.maxPlanetCount)));

        for (size_t i=0;i<planetCnt;i++) {
            double x, y, nowMaxR;
            bool access=true;
            size_t num = ships.size();
            do {
                access = true;
                x = randDouble01() * info.width;
                y = randDouble01() * info.height;
                nowMaxR = double(inf);
                for (size_t j=0; j<num; ++j) {
                    nowMaxR = std::min(nowMaxR, distance(ships[j].x, ships[j].y, x, y)-ships[j].radius);
                }
                for (size_t j=0; j<i; ++j) {
                    nowMaxR = std::min(nowMaxR, distance(planets[j].x, planets[j].y, x, y) - planets[j].radius);
                }
                if (nowMaxR /  (info.minBetweenPercent + 1)<info.minR) access=false;
            } while(!access);
            double r = randomDouble(info.minR, std::min(info.maxR, nowMaxR /  (info.minBetweenPercent + 1)));
            planets.push_back(Planet(x, y, r));
        }

        bombs.resize(info.playerCount);
        for(size_t i=0; i<info.playerCount; ++i) {//开局炮弹藏在天体后面
            bombs[i].x = planets[i].x;
            bombs[i].y = planets[i].y;
        }
    }

    int calculate(size_t id)
    {
        Bomb &bomb=this->bombs[id];
        if (bomb.isCrashed || bomb.id) return -2;
        size_t planetsCnt = planets.size();
        double ax = 0, ay = 0;
        //std::cout << "planetsCnt:" << planetsCnt << std::endl;
        for (size_t i=0; i<planetsCnt; ++i) {
            Planet now = planets[i];
            double s = distance(bomb.x, bomb.y, now.x, now.y);
            ax += (now.getMass() / (SQR(s) / bomb.getMass())) * ((now.x-bomb.x)/s);
            ay += (now.getMass() / (SQR(s) / bomb.getMass())) * ((now.y-bomb.y)/s);
            //std::printf("bomb.getMass():%d",bomb.getMass());
        }
        if (bomb.x < -info.width*info.range || bomb.y<-info.height*info.range || bomb.x>info.width+info.width*info.range || bomb.y>info.height+info.height*info.range) {
            bomb.crash();
            //puts("-1");
            return -1;
        }
        for (size_t i=0;i<planetsCnt;i++) {
            Planet now = planets[i];
            double s = distance(bomb.x, bomb.y, now.x, now.y);
//          std::printf("%lf %lf %lf %lf %lf\n",bomb.x,now.x,bomb.y,now.y,now.r);
            if (std::fabs(s) < now.radius) {
                bomb.crash();

                //puts("-1");
                return -1;
            }
        }
        size_t shipsCnt = ships.size();
        for (size_t i=0; i<shipsCnt; ++i) {
            Ship &now = ships[i];
            double s = distance(bomb.x, bomb.y, now.x, now.y);
            if (std::fabs(s)<now.radius && !now.isFailed) {
                now.isFailed = true;
                bomb.crash();
                return int(i);
            }
        }
        bomb.getNext(ax*info.speed, ay*info.speed);
        return 0;
    }

    Vector <int> multiCalculate()
    {
        Vector <int> result;
        size_t bombsNum=bombs.size();
        for (size_t i=0;i<bombsNum;i++) {
           result.push_back(calculate(i));
        }
        return result;
    }

    int shoot(size_t id, double power, double deg)
    {
        //printf("fucking\n");
        std::cout.flush();
        Bomb &bomb=this->bombs[id];
        //printf("getting end\n");
        std::cout.flush();
        double Sin = std::sin(deg), Cos = std::cos(deg);
        Ship now = ships[id];
        if (now.isFailed)
            return -1;
        bomb = Bomb(now.x+((now.radius+info.eps)*Sin)+info.eps, now.y+((now.radius+info.eps)*Cos), info.shipRadius, true, info.bombDensity, info.speed*Sin*power*info.speedAtBeginning, info.speed*Cos*power*info.speedAtBeginning);
        //printf("bomb updated");
        std::cout.flush();
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
};

#endif // OBJECT_H
