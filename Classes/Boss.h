#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Bullet_Position.h"
#include "Bullet.h"
#include "Function.h"

using namespace CocosDenshion;
USING_NS_CC;

class Boss
{
public:
	Boss(Layer* layer);
	void Boss_SetTarget(Sprite* Spr, Layer* layer);

	Sprite * Hero;
	Layer* Bulletlayer;

	int H_W_Dir;
	int  W_W_Dir;
	float Boss_Hp;
	bool StopRazer;
	bool start;
	bool B_dead;
	bool DeepCircle;//////
	bool CheckWall;
	int count;
	int bulletcount;
	bool Once;
	float Bospeed;
	float Heroangleoffset;

	void Missile(int changeP);
	void MachineGun();
	void Razer();
	void deletRazer();
	Sprite * S_Razer;
	Sprite * BossImage[6];
	Sprite* Space[2];
	Vec2 HeroposMiss;
	void Checkdir(float delta);
	void goCall();
	//
	float Change_X, Change_Y;
	float * Circle;

	BulletPosition *bulletpos;
	Function * F;
	Animate* Missmate;
	//
	double sinTBL[360];
	double cosTBL[360];
	void follow(float bospeed, int changeP);
	void Tracking(Sprite* obj, Point Target, int changeP);
	void Limit(Sprite* obj);
	float Dir = 1000;

	//
	bool complex;
	float natural;
	std::vector<Bullet*> BossBulletContainer;//보스 총알컨테이너
											 //dead

											 //Animation
};