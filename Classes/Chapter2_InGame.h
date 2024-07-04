#pragma once
#include "cocos2d.h"
#include "ChapterSelect.h"
#include "bullet.h"
#include "Hero.h"
#include "Monster.h"
#include "Function.h"
#include "SimpleAudioEngine.h"
#include "Chapter2_2_InGame.h"

using namespace CocosDenshion;

USING_NS_CC;

class InGame_Chapter_2 : public Layer
{
private:
	
public:
	unsigned int FlameSound;
	int Change;
	bool Once;
	
	Function * F;

	void AkimboRemove(float delta);
	UI * ui;
	Weapon * weapon;
	Layer * BulletLayer;
	Hero * hero;//히어로
	Layer * UI_Layer;//UI 레이어
	RepeatForever* BladeDancerRep;

	bool Once2;
	Layer * PauseLayer;

	Sprite * Door[4];

	TMXTiledMap * TileMap; //맵
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);//키보드 함수

	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);//터치함수
	void onMouseMove(cocos2d::Event* event);//마우스 함수

	bool UP, DOWN, RIGHT, LEFT, SHIFT, ESC, Key_4, Skill_4, Key_F;

	void Skill_4_Remove(float delta);

	Sprite * MonsterWeapon[10];

	void menuCallback(Ref * pSender);

	Vec2 Mouse_Position;
	Vec2 MouseScale;
	float Hero_Angle;
	Vec2 Hero_Position;

	Vec2 MonsterObjLayerPos(char * LayerName);
	
	void MonsterCrash();
	void HeroCrash();

	C_Monster * Monster[10];
	bool Fallow[4];//몬스터가 플레이어를 발견하고 따라가는 상태인지
	void RadarMonsterCheak();//몬스터 인지 범위 체크

	Layer * MonsterLayer;
	TMXObjectGroup *objectGroup; //오브젝트
	ValueMap MonsterPoint; //오브젝트에 종속된것

	void Clear();
	void Open();
	static cocos2d::Scene* createScene();

	virtual bool init();
	void goCall();
	void update(float delta);
	void FireCheck(float delta);
	void MonsterFireCheck(float delta);
	CREATE_FUNC(InGame_Chapter_2);
};