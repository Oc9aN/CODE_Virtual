#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Bullet : public Sprite
{
public:
	float FlamethrowerCheak;//È­¿°
	float RemoveTime;
	float dirX, dirY;
	Sprite * DAG_Effect;

	float BulletSpeed;
	bool AfterImage;
	void update(float delta);
	static Bullet * createandinit(float Rotation, float Speed);

};
