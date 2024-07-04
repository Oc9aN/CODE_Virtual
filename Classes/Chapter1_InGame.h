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
	void menuCallback(Ref* pSender);//�޴� �ݹ�

	Layer * PauseLayer;
	UI * ui;
	Weapon * weapon;
	Sprite * MonsterWeapon[8];
	Layer * BulletLayer;
	Hero * hero;//�����
	Layer * UI_Layer;//UI ���̾�
	Layer * Option_Layer;
	RepeatForever* BladeDancerRep;
	TMXTiledMap * TileMap; //��


	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	
	void onMouseMove(cocos2d::Event* event);//���콺 �Լ�

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
	bool Fallow[3];//���Ͱ� �÷��̾ �߰��ϰ� ���󰡴� ��������
	void RadarMonsterCheak();//���� ���� ���� üũ

	Layer * MonsterLayer;
	TMXObjectGroup *objectGroup; //������Ʈ
	ValueMap MonsterPoint; //������Ʈ�� ���ӵȰ�
	static cocos2d::Scene* createScene();

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);//Ű���� �Լ�

	virtual bool init();
	void update(float delta);
	void FireCheck(float delta);
	void MonsterFireCheck(float delta);

	CREATE_FUNC(InGame_Chapter_1);
};
