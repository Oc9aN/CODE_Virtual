#pragma once
#include "cocos2d.h"
#include "Hero.h"
#include "Function.h"
#include "Bullet_Position.h"
#include "Monster.h"
#include "Weapon.h"
#include "Bullet.h"
#include "Singleton.h"
#include "ChapterSelect.h"
#include "UI.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

class InGame_Chapter_1 : public Layer
{
public:
	unsigned int FlameSound;
	int Change;
	bool Once;
	bool Once2;
	void AkimboRemove(float delta);
	void Door_Move();

	bool MonsterClear;

	Function * F;

	Sprite * Door[4];
	bool OpenCheak1, OpenCheak2;
	Menu * Pausebutton_Menu;
	void menuCallback(Ref* pSender);//메뉴 콜백

	Layer * PauseLayer;
	UI * ui;
	Weapon * weapon;
	Sprite * MonsterWeapon[8];
	Layer * BulletLayer;
	Hero * hero;//히어로
	Layer * UI_Layer;//UI 레이어
	Layer * Option_Layer;
	RepeatForever* BladeDancerRep;
	TMXTiledMap * TileMap; //맵


	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	
	void onMouseMove(cocos2d::Event* event);//마우스 함수

	bool UP, DOWN, RIGHT, LEFT, SHIFT, ESC, Skill_4,Key_4,Key_F;

	float Hero_Angle;
	Vec2 Hero_Position;
	Vec2 MouseScale;


	Vec2 Mouse_Position;

	Vec2 MonsterObjLayerPos(char * LayerName);

	void MonsterCrash();
	void Skill_4_Remove(float delta);
	void HeroCrash();

	void goCall();
	C_Monster * Monster[8];
	bool Fallow[3];//몬스터가 플레이어를 발견하고 따라가는 상태인지
	void RadarMonsterCheak();//몬스터 인지 범위 체크

	Layer * MonsterLayer;
	TMXObjectGroup *objectGroup; //오브젝트
	ValueMap MonsterPoint; //오브젝트에 종속된것
	static cocos2d::Scene* createScene();

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);//키보드 함수

	virtual bool init();
	void update(float delta);
	void FireCheck(float delta);
	void MonsterFireCheck(float delta);

	CREATE_FUNC(InGame_Chapter_1);
};
