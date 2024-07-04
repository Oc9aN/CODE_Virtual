#pragma once
#include "cocos2d.h"
#include "UI.h"
#include "Singleton.h"

USING_NS_CC;

class Weapon : public Sprite
{
public:
	static Weapon * createandinit(int a);
	int WeaponCode;
	float Scale;
};
//0:´õºí¹Ù·¿
//1:È­¿°¹æ»ç±â
//2:ÆßÇÁ¼¦°Ç
//3:AK-47
//4:¼­ºê¸Ó½Å°Ç
