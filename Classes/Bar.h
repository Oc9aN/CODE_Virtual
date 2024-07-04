#pragma once
#include "cocos2d.h"

USING_NS_CC;

class UIProgressBar
{

	Layer* ProgressLayer;

public:
	Sprite* backgroundSprite;
	Sprite* foregroundSprite;
	Sprite* midgroundSprite;
	UIProgressBar(Layer* layer);
	void SetPercentage(float fPercent);
	void SetPosition(Vec2 vPos);
	void SetScale(float a, float b);
	void SetForegroundSprite(Sprite* foreSprite);
	void SetBackgroundSprite(Sprite* backSprite);
	void SetmidgroundSprite(Sprite* midSprite);
	void Remove();
};