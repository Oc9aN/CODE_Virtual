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
	Hero * hero;//�����
	Layer * UI_Layer;//UI ���̾�
	RepeatForever* BladeDancerRep;

	bool Once2;
	Layer * PauseLayer;

	Sprite * Door[4];

	TMXTiledMap * TileMap; //��
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);//Ű���� �Լ�

	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);//��ġ�Լ�
	void onMouseMove(cocos2d::Event* event);//���콺 �Լ�

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
	bool Fallow[4];//���Ͱ� �÷��̾ �߰��ϰ� ���󰡴� ��������
	void RadarMonsterCheak();//���� ���� ���� üũ

	Layer * MonsterLayer;
	TMXObjectGroup *objectGroup; //������Ʈ
	ValueMap MonsterPoint; //������Ʈ�� ���ӵȰ�

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