#pragma once
#include "cocos2d.h"
#include "Hero.h"
#include "Function.h"
#include "Bullet_Position.h"
#include "Monster.h"
#include "Weapon.h"
#include "Bullet.h"
#include "ChapterSelect.h"
#include "Singleton.h"
#include "UI.h"

USING_NS_CC;

class InGame_Chapter_2_2 : public Layer
{
private:
	unsigned int FlameSound;
	int Change;
	bool Once;
	
	void AkimboRemove(float delta);
	void Door_Move();

	Function * F;


	Sprite * Door[2];
	Sprite * elevatordoor[2];
	bool Lock;

	bool OpenCheak1, OpenCheak2;

	void menuCallback(Ref* pSender);//메뉴 콜백
	void goCall();

	UI * ui;
	Weapon * weapon;
	Sprite * MonsterWeapon;
	Layer * BulletLayer;
	Hero * hero;//히어로
	Layer * UI_Layer;//UI 레이어
	float time;

	TMXTiledMap * TileMap; //맵

	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);//터치함수
	void onMouseMove(cocos2d::Event* event);//마우스 함수

	bool UP, DOWN, RIGHT, LEFT, SHIFT, ESC, Key_4,Skill_4,Key_F;
	void Skill_4_Remove(float delta);
	bool Once2;
	Layer * PauseLayer;
	float Hero_Angle;
	Vec2 Hero_Position;
	Vec2 MouseScale;

	void MonsterCrash();
	void HeroCrash();

	Vec2 Mouse_Position;
	Vec2 MonsterObjLayerPos(char * LayerName);

	C_Monster * Monster;
	void RadarMonsterCheak();//몬스터 인지 범위 체크

	Layer * MonsterLayer;
	TMXObjectGroup *objectGroup; //오브젝트
	ValueMap MonsterPoint; //오브젝트에 종속된것
public:
	static cocos2d::Scene* createScene();

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);//키보드 함수

	virtual bool init();
	void update(float delta);
	void FireCheck(float delta);
	void MonsterFireCheck(float delta);

	CREATE_FUNC(InGame_Chapter_2_2);
};
