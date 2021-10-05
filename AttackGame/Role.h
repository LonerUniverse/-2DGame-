#pragma once

#include"loadResources.h"

#define LBorder -120
#define RBorder  1024
#define UpBorder  150
#define DownBorder 450
class Role
{
	int x; //x坐标
	int y; //y坐标
	int postion;  //当前位置
	int fullHP;   //血量
	int myself; //1表示自己 0表示敌人
	int HP;     //现有血量

public:
	//构造函数
	Role() {
		x = 50;
		y = 300;
		postion = 1;
		fullHP = 100;
		myself = 1;
		HP = 100;
	}
	~Role() {};

	//初始化
	void init(int X, int Y, int pos, int fullBlood, int Myself, int blood);

	//边界判定与位置改变
	void XMove();
	void YMove();
	//位置右移动移动
	void moveRight()
	{
		x += 30;
	}
	//位置左移动
	void moveLeft()
	{
		x -= 30;
	}
	//位置
	int Pos()
	{
		return postion;
	}
	//位置上移
	void Up() {
		y -= 30;
	}
	//位置下移
	void Down() {
		y += 30;
	}
	//返回X坐标
	int X() {
		return x;
	}
	int Y() {
		return y;
	}
	//改变x的值
	void ChangeX(int value)
	{
		x = value;
	}
	//改变y的值
	void ChangeY(int value)
	{
		y = value;
	}
	//改变位置
	void ChangePos(int pos) {
		postion = pos;
	}
	//返回对象
	int Object()
	{
		return myself;
	}
	//现有血量
	void changeHP(int peopleHP)
	{
		HP -= peopleHP;

	}
	//返回血量
	int NowHP()
	{
		return HP;
	}
	

	//人物血量
	//血量图
	void showHP(int X, int Y, int xx, int yy, int dir) {

		if (dir == 1)
		{
			char HPtext[100]; //MPtext[20];
			sprintf(HPtext, "角色   %d/%d", HP, fullHP);
			//sprintf(MPtext, "MP       %d/%d", MP, fullMP);
			rectangle(X, 1 + Y, 110 + xx, 20 + yy);
			//rectangle(20, 22, 116, 42);
			setfillcolor(RED);
			solidrectangle(1 + X, 2 + Y,10+HP + xx, 19 + yy);
			setbkmode(TRANSPARENT);
			outtextxy(0,3,HPtext);
			//setfillcolor(BLUE);
			//solidrectangle(21, 23, 15 + MP, 41);
			//outtextxy(0, 3, HPtext);
			//outtextxy(0, 25, MPtext);
		}

		if (dir == 0)
		{
			char HPtext_opp[100];
			sprintf(HPtext_opp, "敌人   %d/%d", HP, fullHP);
			rectangle(X, 30 + Y, 110 + xx, 50 + yy);
			
			setfillcolor(RED);
			solidrectangle(1 + X, 31 + Y, 10+HP + xx, 49 + yy);
			setbkmode(TRANSPARENT);
			outtextxy(0, 32, HPtext_opp);

		}

	}
};


//边界判断与人物移动位置改变
//x
void Role::XMove() {
	switch (postion) {
	case 0:
		if (x < LBorder) {
			x = LBorder;
			break;
		}
		moveLeft();

		break;
	case 1:
		if (x > RBorder-230) {
			x = RBorder - 230;
			break;
		}
		moveRight();
			break;
	}
}
//y
void Role::YMove() {
	switch (postion) {
	case 0:
       
		if (y > DownBorder) {
			y = DownBorder;
			break;
		}
         Down();
		break;
	case 1:
          
		if (y < UpBorder) {
			y = UpBorder;
			break;
		}
		Up();
		break;
	}
}
//初始化
void Role::init(int X, int Y, int pos, int fullBlood,int Myself,int blood) {
	x = X;
	y = Y;
	postion = pos;
	fullHP = fullBlood;
	myself = Myself;
	HP = blood;
}

