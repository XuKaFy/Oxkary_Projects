#ifndef OBJECT_H
#define OBJECT_H

#include <cstdlib>
#include <ctime>
#include <vector>

#include <algorithm>

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
    Bomb(real x = 0, real y = 0, real radius = 1, bool movable = true, real density = 1, real vx = 0, real vy = 0, int id = 0)
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
        speedAtBeginning=2;
    }

    int minPlanetCount;
    int maxPlanetCount;
    int playerCount;
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
    real maxPowPerSec;
    real range;
    real shipRadius;
};

#define Vector std::vector

class GravityShooterCore
{
public:
    static double rand01() {
        return rand() / double(RAND_MAX);
    }

    static double random(double Min, double Max) {
        return rand01()*(Max-Min)+Min;
    }

    static double distance(double x1, double y1, double x2, double y2) {
        return sqrt(SQR(x1-x2)+SQR(y1-y2));
    }

    GravityShooterCore(const Info &info = Info())
        : info(info) { }

    Info getInfo() const {
        return info;
    }

    Bomb getBomb() const {
        return bomb;
    }

    void init(const Info &info_new) {
        info = info_new;
        planet.clear();
        ship.clear();

        srand(time(0));
        for (int i=0; i<info.playerCount; ++i) {
            bool access=true;
            double x, y;
            do {
                x = rand01() * info.width, y = rand01() * info.height;
                access=true;
                for (int j=0; j<i; ++j) {
                    if (distance(ship[j].x, ship[j].y, x, y) < info.minDistance)
                        access = false;
                }
            } while(!access);
            ship.push_back(Ship(x, y, info.shipRadius));
        }

        int planetCnt = random(info.minPlanetCount, info.maxPlanetCount);

        for (int i=0;i<planetCnt;i++) {
            double x, y, nowMaxR;
            bool access=true;
            int num = ship.size();
            do {
                access = true;
                x = rand01() * info.width, y = rand01() * info.height;
                nowMaxR = (double)inf;

                for (int j=0; j<num; ++j) {
                    nowMaxR = std::min(nowMaxR, distance(ship[j].x, ship[j].y, x, y));
                }
                for (int j=0; j<i; ++j) {
                    nowMaxR = std::min(nowMaxR, distance(planet[j].x, planet[j].y, x, y) - planet[j].radius);
                }
                if (nowMaxR * info.minBetweenPercent<info.minR) access=false;
            } while(!access);
            double r = random(info.minR, std::min(info.maxR, nowMaxR) * info.minBetweenPercent);
            planet.push_back(Planet(x, y, r));
        }
    }

    int calculate()
    {
        if (bomb.isCrashed || bomb.id) return -2;
        int planetsCnt = planet.size();
        double ax = 0, ay = 0;
        //std::cout << "planetsCnt:" << planetsCnt << std::endl;
        for (int i=0; i<planetsCnt; ++i) {
            Planet now = planet[i];
            double s = distance(bomb.x, bomb.y, now.x, now.y);
            ax += (now.getMass()/(SQR(s))) * ((now.x-bomb.x)/s);
            ay += (now.getMass()/(SQR(s))) * ((now.y-bomb.y)/s);
        }
        if (bomb.x < -info.width*info.range || bomb.y<-info.height*info.range || bomb.x>info.width+info.width*info.range || bomb.y>info.height+info.height*info.range) {
            bomb.crash();

            //puts("-1");
            return -1;
        }
        for (int i=0;i<planetsCnt;i++) {
            Planet now = planet[i];
            double s = distance(bomb.x, bomb.y, now.x, now.y);
//          std::printf("%lf %lf %lf %lf %lf\n",bomb.x,now.x,bomb.y,now.y,now.r);
            if (std::fabs(s) < now.radius) {
                bomb.crash();

                //puts("-1");
                return -1;
            }
        }
        int shipsCnt = ship.size();
        for (int i=0; i<shipsCnt; ++i) {
            Ship &now = ship[i];
            double s = distance(bomb.x, bomb.y, now.x, now.y);
            if (std::fabs(s)<now.radius && !now.isFailed) {
                now.isFailed = true;
                bomb.crash();
                return i;
            }
        }
        bomb.getNext(ax*info.speed, ay*info.speed);

        return 0;
    }

    int shoot(int id, double power, double deg)
    {
        double Sin = std::sin(deg), Cos = std::cos(deg);
        Ship now = ship[id];
        if (now.isFailed)
            return -1;
        bomb = Bomb(now.x+((now.radius+info.eps)*Sin)+info.eps, now.y+((now.radius+info.eps)*Cos), info.shipRadius, true, 0, info.speed*Sin*power*info.speedAtBeginning, info.speed*Cos*power*info.speedAtBeginning);

        return 0;
    }

    const Vector<Planet> &getPlanets() const {
        return planet;
    }

    const Vector<Ship> &getShips() const {
        return ship;
    }

private:
    Info info;
    Vector<Planet> planet;
    Vector<Ship> ship;
    Bomb bomb;
};

#endif // OBJECT_H
