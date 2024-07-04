#pragma once
#include "cocos2d.h"
#include "Function.h"
#include "Bullet.h"
#include "UI.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

class BulletPosition : public Sprite
{
private:
	float  Change_X, Change_Y;
	float * Circle;
public:
	float Bullet_Damage;
	Function * F;
	Layer * bulletLayer;
	void AfterEffect(Sprite * Spr);
	BulletPosition(Layer * layer);

	void bulletPosition(int a, Sprite * Spr, int Akimbo,bool AkimboCheak, bool Container);
	
	std::vector<Bullet*> MonsterbulletContainer;
	std::vector<Bullet*> bulletContainer;//총알 컨테이너
};
