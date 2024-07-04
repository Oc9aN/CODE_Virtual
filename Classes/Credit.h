#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Credit : public Layer
{
private:
	Vec2 MainCenter;
	Label * Name[6];
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	Sprite * CreditImage;

	CREATE_FUNC(Credit);
};