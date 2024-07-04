#pragma once
#include "cocos2d.h"
class Singleton
{
private:
	static Singleton* getInstance;

public:
	static Singleton* GetInstance()
	{
		if (getInstance == NULL)
			getInstance = new Singleton();
		return getInstance;
	}
	int WeaponCode;
	int ClearMode;//0=다시하기, 1=메인메뉴
	bool BGM;
	bool SFX;
};
//0:더블바렛
//1:펌프샷건
//2:AK-47
//3:서브머신건
//4:화염방사기
//5:박격포 
//6:Dead and Gun