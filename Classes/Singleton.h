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
	int ClearMode;//0=�ٽ��ϱ�, 1=���θ޴�
	bool BGM;
	bool SFX;
};
//0:����ٷ�
//1:��������
//2:AK-47
//3:����ӽŰ�
//4:ȭ������
//5:�ڰ��� 
//6:Dead and Gun