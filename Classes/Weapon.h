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
//0:����ٷ�
//1:ȭ������
//2:��������
//3:AK-47
//4:����ӽŰ�
