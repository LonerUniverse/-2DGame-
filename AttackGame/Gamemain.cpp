/*
开发者：刘章项
项目介绍：游戏

*/

#include<conio.h>
#include<iostream>
#include<stdio.h>
#include<time.h>
#include<graphics.h>       //图形库文件
#include<mmsystem.h>
#include"Role.h"
#include"loadResources.h"
#pragma comment(lib,"Winmm.lib")   //播放音乐的api


//主游戏画面
void ShowUI();
//主游戏画面
//按键按下
void keyDown();

//人物找人
void opp_Follow();
//AI对手
void AI();
//数据保存
void SaveData();   //0敌人 1表示自己
//数据读取
void ReadData();

//判断是否获得胜利
void Win();

int state = 0;  //按键状态
int state_opp = 0;  //敌人随机产生一个状态
int isRelease = 0;  //是否放技能


//定义人物并初始化
Role role;
//定义敌方人物
Role opponent;




//开始界面
void startUI() {
	MOUSEMSG Msg;
	ReadData();
	FlushMouseMsgBuffer();
   //加载资源
    putimage(0, 0, &START[0]);
	putimage(415, 333, &START[1]);
	putimage(415, 400, &START[2]);

	EndBatchDraw();
	//播放音乐
	mciSendString("open resources\\Music\\bkmusic.mp3 alias myMusic",NULL,0,NULL);
	mciSendString("play myMusic repeat", NULL, 0, NULL);
     //鼠标点击
	while (1) {
		
		 if(MouseHit()){
         Msg = GetMouseMsg();
		if (Msg.x >= 415 && Msg.x <= 415 + 160 && Msg.y >= 333 && Msg.y <= 333 + 44) {
			putimage(415, 333, &BUTTON[0]);
			Sleep(10);
			if (WM_LBUTTONDOWN == Msg.uMsg) {
				//mciSendString("stop myMusic",NULL,NULL,NULL);
				cleardevice();
				putimage(0, 0, &BKGRD);
				break;
			}
		}
		if (Msg.x >= 415 && Msg.x <= 415 + 160 && Msg.y >= 400 && Msg.y <= 400 + 44) {
			putimage(415, 400, &BUTTON[1]);
			Sleep(10);
			if (WM_LBUTTONDOWN == Msg.uMsg) {
				exit(0);
			}
			else
			putimage(415, 333, &START[1]);
			putimage(415, 400, &START[2]);
		}
		}
	}
}



//主游戏画面
void ShowUI() {
	cleardevice();
	BeginBatchDraw();
	putimage(0, 0, &BKGRD);
	//自己
	putimage(role.X(), role.Y(), 400, 300, &StandY[role.Pos()], 0, 0, SRCAND);
	putimage(role.X(), role.Y(), 400, 300, &Stand[role.Pos()], 0, 0, SRCPAINT);

	//敌人
	putimage(opponent.X(), opponent.Y(), 400, 300, &StandY_opp[opponent.Pos()], 0, 0, SRCAND);
	putimage(opponent.X(), opponent.Y(), 400, 300, &Stand_opp[opponent.Pos()], 0, 0, SRCPAINT);

	//血量
	role.showHP(0, 0, 0, 0, 1);
	opponent.showHP(0, 0, 0, 0, 0);
	EndBatchDraw();
	Sleep(50);
}



//按键按下
void keyDown()
{
	
	//判断是否按下键盘
	if (kbhit()) {
		if (GetAsyncKeyState('A') || GetAsyncKeyState('a'))   //按下相应的键可以执行
		{
		//左移动 0
			isRelease = 1;
			role.ChangePos(0);
			state = 1;
			role.XMove();
		}
		//右移动 1
		if (GetAsyncKeyState('D') || GetAsyncKeyState('d'))
		{
			isRelease = 1;
			role.ChangePos(1);
			state = 1;
			role.XMove();
		}
			//上移动
		if (GetAsyncKeyState('W') || GetAsyncKeyState('w'))
		{
			isRelease = 1;
			role.ChangePos(1);
			role.YMove();
			
			state = 1;	
		}
			//下移动
		if (GetAsyncKeyState('S') || GetAsyncKeyState('s'))
		{
			isRelease = 1;
			role.ChangePos(0);
			role.YMove();
			state = 1;
		}
			//跳跃
		if (GetAsyncKeyState('J') || GetAsyncKeyState('j'))
		{
			isRelease = 1;
			state = 2;
			
		}
			//攻击cut
		if (GetAsyncKeyState('K') || GetAsyncKeyState('k'))
		{
			isRelease = 1;
			state = 3;	
			
		}
			//跳砍
		if (GetAsyncKeyState('U') || GetAsyncKeyState('u'))
		{
			isRelease = 1;
			state = 4;

		}
		
	}
	
}
//技能释放
	void killRelease()
{
		if (isRelease)
		{
			switch (state)
			{
				//站立
			case 0:
			{
				BeginBatchDraw();
				putimage(role.X(), role.Y(), 400, 300, &StandY[role.Pos()], 0, 0, SRCAND);
				putimage(role.X(), role.Y(), 400, 300, &Stand[role.Pos()], 0, 0, SRCPAINT);
				//敌人
				putimage(opponent.X(), opponent.Y(), 400, 300, &StandY_opp[opponent.Pos()], 0, 0, SRCAND);
				putimage(opponent.X(), opponent.Y(), 400, 300, &Stand_opp[opponent.Pos()], 0, 0, SRCPAINT);
				//血量
				role.showHP(0, 0, 0, 0, 1);
				opponent.showHP(0, 0, 0, 0, 0);
				EndBatchDraw();
				break;
			}
			//行走
			case 1:
			{

				for (int i = 0; i < 8; i++) {
					BeginBatchDraw();
					putimage(0, 0, &BKGRD);
					//敌人
					putimage(opponent.X(), opponent.Y(), 400, 300, &StandY_opp[opponent.Pos()], 0, 0, SRCAND);
					putimage(opponent.X(), opponent.Y(), 400, 300, &Stand_opp[opponent.Pos()], 0, 0, SRCPAINT);
					//自己
					putimage(role.X(), role.Y(), 400, 300, &MoveY[role.Pos()], 400 * i, 0, SRCAND);
					putimage(role.X(), role.Y(), 400, 300, &Move[role.Pos()], 400 * i, 0, SRCPAINT);
					//血量
					role.showHP(0, 0, 0, 0, 1);
					opponent.showHP(0, 0, 0, 0, 0);
					EndBatchDraw();
					Sleep(50);
				}
				break;
			}
			//跳
			case 2:
			{

				for (int i = 0; i < 8; i++) {
					BeginBatchDraw();
					putimage(0, 0, &BKGRD);
					//敌人
					putimage(opponent.X(), opponent.Y(), 400, 300, &StandY_opp[opponent.Pos()], 0, 0, SRCAND);
					putimage(opponent.X(), opponent.Y(), 400, 300, &Stand_opp[opponent.Pos()], 0, 0, SRCPAINT);
					//自己
					putimage(role.X(), role.Y(), 400, 300, &JumpY[role.Pos()], 400 * i, 0, SRCAND);
					putimage(role.X(), role.Y(), 400, 300, &Jump[role.Pos()], 400 * i, 0, SRCPAINT);
					//血量
					role.showHP(0, 0, 0, 0, 1);
					opponent.showHP(0, 0, 0, 0, 0);
					EndBatchDraw();
					Sleep(50);
				}

				break;
			}
			//砍
			case 3:
			{

				mciSendString("open resources\\Music\\cut.wav alias music", 0, 0, 0);
				mciSendString("play music from 0", 0, 0, 0);
				for (int i = 0; i < 7; i++) {
					BeginBatchDraw();
					putimage(0, 0, &BKGRD);
					//敌人
					putimage(opponent.X(), opponent.Y(), 400, 300, &StandY_opp[opponent.Pos()], 0, 0, SRCAND);
					putimage(opponent.X(), opponent.Y(), 400, 300, &Stand_opp[opponent.Pos()], 0, 0, SRCPAINT);
					//自己
					putimage(role.X(), role.Y(), 400, 300, &RoleCutY[role.Pos()], 400 * i, 0, SRCAND);
					putimage(role.X(), role.Y(), 400, 300, &RoleCut[role.Pos()], 400 * i, 0, SRCPAINT);
					//血量
					role.showHP(0, 0, 0, 0, 1);
					opponent.showHP(0, 0, 0, 0, 0);
					EndBatchDraw();
					Sleep(50);
				}

				break;
			}
			//跳砍
			case 4:
			{

				//播放音乐
				mciSendString("open resources\\Music\\cut1.wav alias music", 0, 0, 0);
				mciSendString("play music from 0", 0, 0, 0);
				for (int i = 0; i < 6; i++) {
					BeginBatchDraw();
					putimage(0, 0, &BKGRD);
					//敌人
					putimage(opponent.X(), opponent.Y(), 400, 300, &StandY_opp[opponent.Pos()], 0, 0, SRCAND);
					putimage(opponent.X(), opponent.Y(), 400, 300, &Stand_opp[opponent.Pos()], 0, 0, SRCPAINT);
					//自己
					putimage(role.X(), role.Y(), 400, 300, &JumpCutY[role.Pos()], 400 * i, 0, SRCAND);
					putimage(role.X(), role.Y(), 400, 300, &JumpCut[role.Pos()], 400 * i, 0, SRCPAINT);
					//血量
					role.showHP(0, 0, 0, 0, 1);
					opponent.showHP(0, 0, 0, 0, 0);
					EndBatchDraw();
					Sleep(50);
				}
				opponent.changeHP(10);
				//伴随技能
				for (int i = 0; i < dgSkillFrames; i++) {
					BeginBatchDraw();
					putimage(opponent.X() + 100, opponent.Y(), &dragonSkillY[i], SRCAND);
					putimage(opponent.X() + 100, opponent.Y(), &dragonSkill[i], SRCPAINT);
					
					//血量
					role.showHP(0, 0, 0, 0, 1);
					opponent.showHP(0, 0, 0, 0, 0);
					EndBatchDraw();
					Sleep(20);
				}
				break;

			}
			
			}
          isRelease = 0;
		}

 }


//人物找人
	void opp_Follow()
	{
		
		switch (state_opp)
		{
			//站立
		case 0:
		{
			BeginBatchDraw();
			//自己
			putimage(role.X(), 300, 400, 300, &StandY[role.Pos()], 0, 0, SRCAND);
			putimage(role.X(), 300, 400, 300, &Stand[role.Pos()], 0, 0, SRCPAINT);
			//敌人
			putimage(600, opponent.Y(), 400, 300, &StandY_opp[opponent.Pos()], 0, 0, SRCAND);
			putimage(600, opponent.Y(), 400, 300, &Stand_opp[opponent.Pos()], 0, 0, SRCPAINT);
			//血量
			role.showHP(0, 0, 0, 0, 1);
			opponent.showHP(0, 0, 0, 0, 0);
			EndBatchDraw();
			break;
		}
		//行走
		case 1:
		{

			for (int i = 0; i < 8; i++) {
				BeginBatchDraw();
				putimage(0, 0, &BKGRD);
				//自己
				putimage(role.X(), role.Y(), 400, 300, &StandY[role.Pos()], 0, 0, SRCAND);
				putimage(role.X(), role.Y(), 400, 300, &Stand[role.Pos()], 0, 0, SRCPAINT);
				//敌人
				putimage(opponent.X(), opponent.Y(), 400, 300, &MoveY_opp[opponent.Pos()], 400 * i, 0, SRCAND);
				putimage(opponent.X(), opponent.Y(), 400, 300, &Move_opp[opponent.Pos()], 400 * i, 0, SRCPAINT);
				//血量
				role.showHP(0, 0, 0, 0, 1);
				opponent.showHP(0, 0, 0, 0, 0);
				EndBatchDraw();
				Sleep(50);

			}

			break;
		
		}
		//跳
		case 2:
		{
			BeginBatchDraw();
			for (int i = 0; i < 8; i++) {
				putimage(0, 0, &BKGRD);
				//自己
				putimage(role.X(), role.Y(), 400, 300, &StandY[role.Pos()], 0, 0, SRCAND);
				putimage(role.X(), role.Y(), 400, 300, &Stand[role.Pos()], 0, 0, SRCPAINT);
				//敌人
				putimage(opponent.X(), opponent.Y(), 400, 300, &JumpY_opp[opponent.Pos()], 400 * i, 0, SRCAND);
				putimage(opponent.X(), opponent.Y(), 400, 300, &Jump_opp[opponent.Pos()], 400 * i, 0, SRCPAINT);
				//血量
				role.showHP(0, 0, 0, 0, 1);
				opponent.showHP(0, 0, 0, 0, 0);
				EndBatchDraw();
			 Sleep(50);
               
			}
			
			break;
		}
		//砍
		case 3:
		{
			
			mciSendString("open resources\\Music\\cut.wav alias music", 0, 0, 0);
			mciSendString("play music from 0", 0, 0, 0);
			role.changeHP(3);
			for (int i = 0; i < 7; i++) {
               BeginBatchDraw();
				putimage(0, 0, &BKGRD);
				//自己
				putimage(role.X(), role.Y(), 400, 300, &StandY[role.Pos()], 0, 0, SRCAND);
				putimage(role.X(), role.Y(), 400, 300, &Stand[role.Pos()], 0, 0, SRCPAINT);
				//敌人
				putimage(opponent.X(), opponent.Y(), 400, 300, &RoleCutY_opp[opponent.Pos()], 400 * i, 0, SRCAND);
				putimage(opponent.X(), opponent.Y(), 400, 300, &RoleCut_opp[opponent.Pos()], 400 * i, 0, SRCPAINT);
				//血量
				role.showHP(0, 0, 0, 0, 1);
				opponent.showHP(0, 0, 0, 0, 0);
                EndBatchDraw();
				Sleep(50);
			}
			
			break;
		}
		//跳砍
		case 4:
		{
			
			//播放音乐
			mciSendString("open resources\\Music\\rain.wav alias music", 0, 0, 0);
			mciSendString("play music from 0", 0, 0, 0);
			for (int i = 0; i < 6; i++) {
              BeginBatchDraw();
				putimage(0, 0, &BKGRD);
				//自己
				putimage(role.X(), role.Y(), 400, 300, &StandY[role.Pos()], 0, 0, SRCAND);
				putimage(role.X(), role.Y(), 400, 300, &Stand[role.Pos()], 0, 0, SRCPAINT);
				//敌人
				putimage(opponent.X(), opponent.Y(), 400, 300, &JumpCutY_opp[opponent.Pos()], 400 * i, 0, SRCAND);
				putimage(opponent.X(), opponent.Y(), 400, 300, &JumpCut_opp[opponent.Pos()], 400 * i, 0, SRCPAINT);
				//血量
				role.showHP(0, 0, 0, 0, 1);
				opponent.showHP(0, 0, 0, 0, 0);
                 EndBatchDraw();
				Sleep(50);
			}
			
			//伴随技能
			if (opponent.Pos() == 1)
			{
				
				for (int i = 0; i < frameRain; i++) {
                     BeginBatchDraw();
					//putimage(opponent.X() + 200, opponent.Y(), &rainSkillY[i], SRCAND);
					putimage(role.X(), role.Y()-150, &rainSkill[i], SRCPAINT);
					//血量
					role.showHP(0, 0, 0, 0, 1);
					opponent.showHP(0, 0, 0, 0, 0);
					EndBatchDraw();
					Sleep(50);
				}
			}
			else
				{
				
					for (int i = 0; i < frameRain; i++) {
                     BeginBatchDraw();
						//putimage(opponent.X() - 200, opponent.Y(), &rainSkillY[i], SRCAND);
						putimage(role.X(), role.Y()-150, &rainSkill[i], SRCPAINT);
						//血量
						role.showHP(0, 0, 0, 0,1);
						opponent.showHP(0, 0, 0, 0,0);
                      EndBatchDraw();
					  Sleep(50);
					}
					
				}
				
			}
			break;
		
		}

		state_opp = 0;
	}
	//AI对手
	void AI()
	{
		if ((role.X() - opponent.X()) >= 30 || (role.X() - opponent.X()) <= -30)
		{
			state_opp = 1;
			opponent.XMove();

		}
		
		else
		{
			state_opp = 3 + rand() % 6;
			role.changeHP(5);
		}
			

	}
	//数据保存
void SaveData()   //0敌人 1表示自己
	{
	int HP = role.NowHP();
	int opp_HP = opponent.NowHP();
	FILE *fp_role;
	FILE*fp_opp;
	
	
	fp_role = fopen("Data\\RoleData.dat", "w+");
	 fp_opp =fopen("Data\\oppData.dat", "w+");
	 
	fprintf(fp_role,"%d",HP);	
			
	fprintf(fp_opp,"%d",opp_HP);
	fclose(fp_role);
	fclose(fp_opp);
	}


void ReadData() {

	FILE *fp_role, *fp_opp;
	int HP = role.NowHP();
	int opp_HP = opponent.NowHP();
	if ((fp_role = fopen("Data\\RoleData.dat", "rb")) == NULL)
	{
		MessageBox(NULL, _T("文件不存在！！将重新开始..."), _T("检查文件"),MB_OK);
	}
	if ((fp_opp = fopen("Data\\oppData.dat", "rb+")) == NULL)
	{
		MessageBox(NULL, _T("文件不存在！！将重新开始..."), _T("检查文件"), MB_OK);
	}

	fscanf(fp_role, "%d",&HP);

	fscanf(fp_opp, "%d",&opp_HP);
	fclose(fp_role);
	fclose(fp_opp);
		

	}

//判断是否获得胜利
void Win()
{
	if (opponent.NowHP() <= 0)
	{
		putimage(300, 200, &Victory);
		Sleep(500);
		MessageBox(NULL, _T("游戏将重新开始..."), _T("胜利"), MB_OK);
		opponent.init(600, role.Y(), 0, 100, 0, 100);
		role.init(50,300,1,100,1,100);
		startUI();
		
	}
	if (role.NowHP() <= 0) {

		putimage(300, 200, &Fail);
		Sleep(500);
		MessageBox(NULL, _T("游戏将重新开始..."), _T("失败"), MB_OK);
		opponent.init(600, role.Y(), 0, 100, 0, 100);
		role.init(50, 300, 1, 100, 1, 100);
		startUI();
	}

}
int main(int argv, char*argc[])
{
	
	//随机数种子
	srand((unsigned)time(NULL));
    //创建窗口
	initgraph(WIDTH, HEIGHT);  //NOCLOSE不能关闭窗口
	loadResources();
    //敌方人物初始化
    opponent.init(600,role.Y(),0,100,0,100);
	//开始界面
	startUI();
	
	while (1) {
		//1 显示背景和人物
		  ShowUI();
		//2 按键按下改变人物位置信息
		  keyDown();
		  killRelease();
		  AI();
		  opp_Follow();
		//3 重新显示场景信息
		  SaveData();
		  Win();
		
	}
	closegraph();
	return 0;
}
