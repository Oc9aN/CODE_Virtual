#pragma once
#include "cocos2d.h"
#include "Credit.h"
#include "Singleton.h"
#include "Bar.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

class UI : public Layer
{
public:
	UI(Layer * layer);
	void Option(Layer *layer);
	void Sound();
	Sprite * Magazine;
	Sprite * Skill_Number[4];
	Sprite * Clear_Background;
	Label * Magazine_Label;
	Sprite * Health_bar;
	
	UIProgressBar * bar;
	
	Sprite * HandImage;

	bool Clear;
	int Magazine_Num;
	MenuItemImage *Skill_Image[4];
	Sprite * Skill_Button;

	Layer * ClearLayer;
	
	void menuCallback(Ref * pSender);

	void update(int a);
	void Hero_Update(int a);
	void Magazine_Animation();
	void LifeImageCheck(int a);
};
