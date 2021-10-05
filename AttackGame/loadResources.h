#pragma once
#include<graphics.h>
#include<stdio.h>
#define WIDTH 1024
#define HEIGHT 666
#define PosX 50
#define PosY 300
#define dragonFrames 6   //飞行龙的帧数
#define dgSkillFrames 40  //释放龙的技能
#define strNum  100
#define frameRain 8
//开始界面图片
IMAGE START[3];
IMAGE BUTTON[5];
IMAGE BKGRD;

//人物的站立
IMAGE Stand[2];
IMAGE StandY[2];

//人物移动
IMAGE Move[2];
IMAGE MoveY[2];

//人物跳
IMAGE Jump[4];
IMAGE JumpY[4];
//人物砍
IMAGE RoleCut[2];
IMAGE RoleCutY[2];
//人物跳砍
IMAGE JumpCut[4];
IMAGE JumpCutY[4];

//敌方人物的加载-------------

//人物的站立
IMAGE Stand_opp[2];
IMAGE StandY_opp[2];

//人物移动
IMAGE Move_opp[2];
IMAGE MoveY_opp[2];

//人物跳
IMAGE Jump_opp[4];
IMAGE JumpY_opp[4];
//人物砍
IMAGE RoleCut_opp[2];
IMAGE RoleCutY_opp[2];
//人物跳砍
IMAGE JumpCut_opp[4];
IMAGE JumpCutY_opp[4];



//龙的技能释放
IMAGE dragonSkill[39];
IMAGE dragonSkillY[39];

//流星雨技能
IMAGE rainSkill[8];
IMAGE rainSkillY[8];

//胜利
IMAGE Victory;
IMAGE Fail;



//加载资源
void loadResources() {

	//加载图片
	loadimage(&START[0], "resources\\Background\\Login.png", WIDTH, HEIGHT);
	loadimage(&START[1], "resources\\Button\\entry.png");
	loadimage(&START[2], "resources\\Button\\quit.png");
	loadimage(&BUTTON[0], "resources\\Button\\entry1.png");
	loadimage(&BUTTON[1], "resources\\Button\\quit1.png");

	//进入界面
	loadimage(&BKGRD, "resources\\Background\\background1.jpg", WIDTH, HEIGHT);

	//加载人物
	loadimage(&Stand[0], "resources\\Stand\\left.bmp");
	loadimage(&Stand[1], "resources\\Stand\\right.bmp");
	loadimage(&StandY[0], "resources\\Stand\\lefty.bmp");
	loadimage(&StandY[1], "resources\\Stand\\righty.bmp");

	//加载人物移动图片
	loadimage(&Move[0], "resources\\Move\\left.bmp");
	loadimage(&Move[1], "resources\\Move\\right.bmp");
	loadimage(&MoveY[0], "resources\\Move\\lefty.bmp");
	loadimage(&MoveY[1], "resources\\Move\\righty.bmp");

	//人物跳
	FlushBatchDraw();
	loadimage(&Jump[0], "resources\\Jump\\left.bmp");
	loadimage(&Jump[1], "resources\\Jump\\right.bmp");
	loadimage(&JumpY[0], "resources\\Jump\\lefty.bmp");
	loadimage(&JumpY[1], "resources\\Jump\\righty.bmp");

	//人物砍
	loadimage(&RoleCut[0], "resources\\Cut\\left.bmp");
	loadimage(&RoleCut[1], "resources\\Cut\\right.bmp");
	loadimage(&RoleCutY[0], "resources\\Cut\\lefty.bmp");
	loadimage(&RoleCutY[1], "resources\\Cut\\righty.bmp");

	//人物跳砍
	loadimage(&JumpCut[0], "resources\\JumpCut\\left.bmp");
	loadimage(&JumpCut[1], "resources\\JumpCut\\right.bmp");
	loadimage(&JumpCutY[0], "resources\\JumpCut\\lefty.bmp");
	loadimage(&JumpCutY[1], "resources\\JumpCut\\righty.bmp");

	
	//加载敌方------------------------------------------------------
	//加载人物
	loadimage(&Stand_opp[0], "resources\\Stand\\left_opponent.bmp");
	loadimage(&Stand_opp[1], "resources\\Stand\\right_opponent.bmp");
	loadimage(&StandY_opp[0], "resources\\Stand\\lefty.bmp");
	loadimage(&StandY_opp[1], "resources\\Stand\\righty.bmp");

	//加载人物移动图片
	loadimage(&Move_opp[0], "resources\\Move\\left_opponent.bmp");
	loadimage(&Move_opp[1], "resources\\Move\\right_opponent.bmp");
	loadimage(&MoveY_opp[0], "resources\\Move\\lefty.bmp");
	loadimage(&MoveY_opp[1], "resources\\Move\\righty.bmp");

	//人物跳

	loadimage(&Jump_opp[0], "resources\\Jump\\left_opponent.bmp");
	loadimage(&Jump_opp[1], "resources\\Jump\\right_opponent.bmp");
	loadimage(&JumpY_opp[0], "resources\\Jump\\lefty.bmp");
	loadimage(&JumpY_opp[1], "resources\\Jump\\righty.bmp");

	//人物砍
	loadimage(&RoleCut_opp[0], "resources\\Cut\\left_opponent.bmp");
	loadimage(&RoleCut_opp[1], "resources\\Cut\\right_opponent.bmp");
	loadimage(&RoleCutY_opp[0], "resources\\Cut\\lefty.bmp");
	loadimage(&RoleCutY_opp[1], "resources\\Cut\\righty.bmp");

	//人物跳砍
	loadimage(&JumpCut_opp[0], "resources\\JumpCut\\left_opponent.bmp");
	loadimage(&JumpCut_opp[1], "resources\\JumpCut\\right_opponent.bmp");
	loadimage(&JumpCutY_opp[0], "resources\\JumpCut\\lefty.bmp");
	loadimage(&JumpCutY_opp[1], "resources\\JumpCut\\righty.bmp");


	
	//加载龙的技能
	for (int i = 1; i < dgSkillFrames; i++) {
		//加载大的图片
		char Str[strNum] = "";
		char StrY[strNum] = "";
		sprintf(Str, "resources\\SuperSkill\\Dragon\\%d.png", i);
		sprintf(StrY, "resources\\SuperSkill\\DragonY\\%d.png", i);
		loadimage(&dragonSkill[i - 1], Str);
		loadimage(&dragonSkillY[i - 1], StrY);
	}
	

	//加载流星雨技能
	for (int i = 1; i < frameRain; i++) {
		char Str[strNum] = "";
		char StrY[strNum] = "";
		sprintf(Str, "resources\\SuperSkill\\RainSkill\\%d.png", i);
		sprintf(StrY, "resources\\SuperSkill\\RainSkillY\\%d.png", i);
		loadimage(&rainSkill[i - 1], Str);
		loadimage(&rainSkillY[i - 1], StrY);
	}

	loadimage(&Victory, "resources\\Background\\win.png");
	loadimage(&Fail, "resources\\Background\\fail.png");

}


