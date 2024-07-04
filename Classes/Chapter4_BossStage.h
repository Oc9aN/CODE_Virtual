#pragma once
#include "cocos2d.h"
#include "Hero.h"
#include "Weapon.h"
#include "Bullet.h"
#include "Singleton.h"
#include "UI.h"
#include "Boss.h"
#include "Function.h"
#include "ChapterSelect.h"
#include "Bullet_Position.h"
#include "Bar.h"


USING_NS_CC;

class InGame_Boss : public Layer
{
private:
	unsigned int FlameSound;
	int Change;
	int PlusMissile = 0;
	void goCall();
	void AkimboRemove(float delta);
	int I;//보스죽을떄사용하는변수 건들면 D짐
	void Door_Move();
	bool Lock;
	Sprite * Door[4];
	Sprite * D_bosspos[10];
	Sprite * oppa;
	Sprite * chip[8];
	UI * ui;
	Weapon * weapon;
	Function * F;
	Layer * BulletLayer;
	Hero * hero;//히어로
	Layer * UI_Layer;//UI 레이어

	TMXTiledMap * TileMap; //맵
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);//키보드 함수

	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);//터치함수
	void onMouseMove(cocos2d::Event* event);//마우스 함수

	bool Once;
	bool UP, DOWN, RIGHT, LEFT, SHIFT, ESC, Skill_4, Key_4;
	float Hero_Angle;
	Vec2 Hero_Position;
	Vec2 Mouse_Position;
	Vec2 MouseScale;
	void menuCallback(Ref* pSender);//메뉴 콜백
	Layer * PauseLayer;
	Layer * Option_Layer;
	void Skill_4_Remove(float delta);


	UIProgressBar * bar;
	TMXObjectGroup *objectGroup; //오브젝트
	ValueMap MonsterPoint; //오브젝트에 종속된것
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void update(float delta);
	void FireCheck(float delta);

	void MonsterCrash();
	void HeroCrash();

	//보스와관련됫것들...
	char arr[50];
	Label * Boss_guage;
	Layer* BossLayer;
	Boss * boss;
	Animate* Aniamate[8];
	Vec2 Bosspos;
	bool BossPause;
	int pattern;
	int changeP;
	int Bospeed;
	Bullet* bullet;
	void Fire_Missile_Check(float delta);
	void Fire_MushineGun_Check(float delta);
	void Fire_Razer(float delta);
	void F_chip();
	void Boss_Dead(float delta);
	//원의방정식
	//16

	CREATE_FUNC(InGame_Boss);
};