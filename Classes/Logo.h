#pragma once
#include "cocos2d.h"
#include "ChapterSelect.h"
#include "Singleton.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

class Logo : public cocos2d::Layer
{
private:
	Sprite * MainMenu_Background[2];
	Sprite * Game_Name;
	Sprite * Play;
	Action * Open_Action[2];
public:
    static cocos2d::Scene* createScene();

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    virtual bool init();

	void ChangeScene();

	bool onTouchBegan(Touch * touch, Event * event);
	void onTouchEnded(Touch * touch, Event * event);
  
    CREATE_FUNC(Logo);
};
