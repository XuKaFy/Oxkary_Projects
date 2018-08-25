#include <bits/stdc++.h>
#define minR 2
#define maxR 30
#define minBetweenPercent 0.5
#define maxFlyFrames
#define eps 1
#define maxPowPerSec 1
struct Ship {
	double x,y;
	int color;//颜色（6位16进制颜色代码）
	bool isFailed;
	int shootCounts;//射爆几次
	Ship(double x=0,double y=0,int color=0):x(x),y(y),color(color),isFailed(false),shootCounts(0) {};
};

struct Bomb {
	double x,y;//坐标
	double vx,vy;//水平/垂直方向速度
	int id;//所属飞船
	int color;//颜色（6位16进制颜色代码）
	bool isCrashed;//是否已碰撞
	Bomb(double x=0,double y=0,double vx=0,double vy=0,int id=-1,int color=0):x(x),y(y),vx(vx),vy(vy),color(color),isCrashed(false) {};
};

struct Plannet {
	double x,y;//坐标
	double r,M;//半径,质量
	int color;//颜色（6位16进制颜色代码）
//	bool isDeleted;
	Plannet(double x=0,double y=0,double r=0,int color=0):x(x),y(y),r(r),M(r*r),color(color) {};
};

class Info
{
private:
	int	minPlannets,maxPlannets,playerCounts,minDis,height,width;//最少星球数，最大星球数，玩家数量，玩家最近间隔，高度，宽度
//		double minR;
	std::vector <Ship> ships;//飞船
	std::vector <Plannet> plannets;//星球
	Bomb bomb;
public:
	Info() {};
	void init(int minPlannets,int maxPlannets,int playerCounts,int minDis,int height,int width)
	{
//			this->minR=minR;
		this->minPlannets=minPlannets;
		this->maxPlannets=maxPlannets;
		this->playerCounts=playerCounts;
		this->minDis=minDis;
		this->height=height;
		this->width=width;
	}
	int getWidth() {return width;}
	int getHeight() {return height;}
	int getShipsNum() {	return ships.size();}
	int getPlannetsNum() {return ships.size();}
	void setBomb(double x,double y,double vx,double vy,int id,bool crashed)
	{
		bomb.x=x;
		bomb.y=y;
		bomb.vx=vx;
		bomb.vy=vy;
		bomb.id=id;
		bomb.isCrashed=crashed;
	}
	Bomb getBomb() {return bomb;}
	void failShip(int i)
	{
		if (i>=(int)ships.size()) assert(0);
		ships[i].isFailed=true;
	}
	void plusShootCnt(int id)
	{
		if (id>=(int)ships.size()) assert(0);
		ships[id].shootCounts++;
	}
	void crashBomb() {bomb.isCrashed=true;}
	int getNowShip()
	{
		if (bomb.isCrashed) return 0;
		else return bomb.id;
	}
	bool flying() {return !bomb.isCrashed;}
	void addPlannet(double x,double y,double r) {plannets.push_back(Plannet (x,y,r)); }
	Plannet getPlannet(int i)
	{
		if (i>=(int)plannets.size()) assert(0);
		return plannets[i];
	}
	Ship getShip(int i)
	{
		if (i>=(int)ships.size()) assert(0);
		return ships[i];
	}
	Ship addShip(double x,double y,int color)
	{
		Ship now(x,y,color);
		ships.push_back(now);
		return now;
	}

//		void
};

class GravityShooter
{
//	private:

//		int	minPlannets,maxPlannets,playerCounts,minDis,height,width;
public:Info shooter;
	static double rand01()  //返回介于0~1之间的随机浮点数
	{
		double ran=rand() / double(RAND_MAX);
		return ran;
	}

	static double random(double Min,double Max)
	{
		return rand01()*(Max-Min)+Min;
	}

	static double dis(double x1,double y1,double x2,double y2)
	{
		return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	}

	void init(int minPlannets,int maxPlannets,int playerCounts,int minDis,int height,int width,std::vector <int> colors)
	{

		srand(time(0));
		shooter.init(minPlannets,maxPlannets,playerCounts,minDis,height,width);
		for (int i=0; i<playerCounts; i++) {
			bool access=true;
			double x,y;
			do {
				x=rand01()*width,y=rand01()*height;
				access=true;
				for (int j=0; j<i; j++) {
					Ship now=shooter.getShip(j);
					if (dis(now.x,now.y,x,y)>minDis)
						access=false;
				}
			} while(!access);
			shooter.addShip(x,y,colors[i]);
		}
		int plannetCnt=random(minPlannets,maxPlannets);
		for (int i=0; i<plannetCnt; i++) {
			double x,y,nowMaxR;
			bool access=true;
			int num=shooter.getShipsNum();
			do {
				access=true;
				x=rand01()*width,y=rand01()*height;
				nowMaxR=999999999.0;
				for (int j=0; j<num; j++) {
					Ship now=shooter.getShip(j);
					nowMaxR=std::min(nowMaxR,dis(now.x,x,now.y,y));
				}
				if (nowMaxR*minBetweenPercent<minR) access=false;
			} while(!access);
			double r=random(minR,nowMaxR*minBetweenPercent);
			shooter.addPlannet(x,y,r);
		}
	}

	int calculate()
	{
		Bomb bomb=shooter.getBomb();
		if (bomb.isCrashed||bomb.id==-1) return -2;//异常
		int plannetsCnt=shooter.getPlannetsNum();
		double ax=0,ay=0;
		for (int i=0; i<plannetsCnt; i++) {
			Plannet now=shooter.getPlannet(i);
			double s=dis(bomb.x,now.x,bomb.y,now.y);
			ax+=(now.M/(s*s))*((now.x-bomb.x)/s);
			ay+=(now.M/(s*s))*((now.y-bomb.y)/s);
		}
		if (bomb.x<-500||bomb.y<-500||bomb.x>shooter.getWidth()+500||bomb.y>shooter.getHeight()+500) {
			shooter.crashBomb();
			return -1;
		}
		for (int i=0; i<plannetsCnt; i++) {
			Plannet now=shooter.getPlannet(i);
			double s=dis(bomb.x,now.x,bomb.y,now.y);
			if (std::fabs(s)<eps) {
				shooter.crashBomb();
				return -1;
			}
		}
		int shipsCnt=shooter.getShipsNum();
		for (int i=0; i<shipsCnt; i++) {
			Ship now=shooter.getShip(i);
			double s=dis(bomb.x,now.x,bomb.y,now.y);
			if (std::fabs(s)<eps&&now.isFailed==false) {
				shooter.failShip(i);
				shooter.crashBomb();
				return i;
			}
		}
		std::cout<<"ax:"<<ax<<"    ay:"<<ay<<std::endl;
		shooter.setBomb(bomb.x+bomb.vx,bomb.y+bomb.vy,bomb.vx+ax,bomb.vy+ay,bomb.id,bomb.color);
		return 0;
	}

	int shoot(int id,double power,double deg) //Deg为弧度制
	{
		shooter.plusShootCnt(id);
		double Sin=std::sin(deg),Cos=std::cos(deg);
		Ship now=shooter.getShip(id);
		shooter.setBomb(now.x,now.y,maxPowPerSec*Sin*power,maxPowPerSec*Cos*power,id,0);


		//debug
//			std::cout<<"hello:"<<shooter.getBomb().id<<std::endl;
		return 0;
	}

	Bomb getBomb()//作废
	{
		return shooter.getBomb();
	}
} Game;
int main()
{
	std::vector <int> a;
	a.push_back(666);
	a.push_back(666);
	a.push_back(666);
//
	Game.init(2,4,2,10,100,100,a);
	Game.shoot(0,0,0.25*3.1415926536);
	while(1) {
		Game.calculate();
		std::cout<<Game.getBomb().x<<"  "<<Game.getBomb().y<<"   "<<Game.getBomb().vx<<"   "<<Game.getBomb().vy<<"   "<<"   "<<Game.getBomb().isCrashed<<std::endl;
		for (int i=1; i<=100000000; i++) ;
	}
}
