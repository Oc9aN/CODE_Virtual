#pragma once
#include "cocos2d.h"
#include "Bullet_Position.h"

USING_NS_CC;

class Hero
{
public:
	Hero(Layer *layer);
	Sprite * HeroImage;
	Sprite * Space;
	Sprite * ShieldSpace;
	float FireDelay;
	bool ShotCheck;
	Sprite * HandSprite;

	BulletPosition * bulletposition;
	int Hero_HP;
	bool Invincibility;//¹«Àû
	bool AkimboCheak;

	bool NoDead;
	bool HeroContainerCheck;
	void Shield();
	void HeroChange(int a,bool Akimbo);
};
