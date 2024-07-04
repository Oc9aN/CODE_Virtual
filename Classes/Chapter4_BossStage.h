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
	int I;//��������������ϴº��� �ǵ�� D��
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
	Hero * hero;//�����
	Layer * UI_Layer;//UI ���̾�

	TMXTiledMap * TileMap; //��
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);//Ű���� �Լ�

	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);//��ġ�Լ�
	void onMouseMove(cocos2d::Event* event);//���콺 �Լ�

	bool Once;
	bool UP, DOWN, RIGHT, LEFT, SHIFT, ESC, Skill_4, Key_4;
	float Hero_Angle;
	Vec2 Hero_Position;
	Vec2 Mouse_Position;
	Vec2 MouseScale;
	void menuCallback(Ref* pSender);//�޴� �ݹ�
	Layer * PauseLayer;
	Layer * Option_Layer;
	void Skill_4_Remove(float delta);


	UIProgressBar * bar;
	TMXObjectGroup *objectGroup; //������Ʈ
	ValueMap MonsterPoint; //������Ʈ�� ���ӵȰ�
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void update(float delta);
	void FireCheck(float delta);

	void MonsterCrash();
	void HeroCrash();

	//�����Ͱ��õ̰͵�...
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
	//���ǹ�����
	//16

	CREATE_FUNC(InGame_Boss);
};