#pragma once
#include "cocos2d.h"
#include "Chapter1_InGame.h"
#include "Chapter2_InGame.h"
#include "Chapter4_BossStage.h"
#include "UI.h"
#include "Function.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

class ChapterSelect : public Layer
{
private:	
	UI * ui;
	Vec2 SightOff;
	Vec2 MainCenter;

	Sprite * Chapter[2];
	Sprite * Number[2][2];
	Sprite * WhiteSide[2][2];
	Sprite * Chapter_Backgrond;

	MenuItemImage * Chapter_Number[2][2];
	MenuItemImage * Chapter_Number2[2][2];
	MenuItemImage * Pink_On[2];
	MenuItemImage * Pink_Off[2];
	MenuItemToggle * toggle[2];
	MenuItemImage * Chapter_1;
	MenuItemImage * Chapter_2;
	MenuItemImage * Pink[2];

	Menu * PinkMenu;
	Menu * OptionMenu;
	Menu * menu;
	Menu * ChapterMenu;
	Menu * ChapterMenu2;

	Layer * Chapter_Layer[2];
	Layer * Option_Layer;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void Chapteronce(float delta);

	void onMouseMove(cocos2d::Event* event);//마우스 함수

	void ChapterSelect::menuCallback(cocos2d::Ref* pSender);


	CREATE_FUNC(ChapterSelect);
};
