#pragma once
#include "cocos2d.h"
#include "bullet.h"
#include "Function.h"
#include "Bullet_Position.h"
#include "Bar.h"

USING_NS_CC;
enum MonsterState
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
};
class C_Monster :public Layer
{
public:
	C_Monster(Layer *layer);

	Function * F;

	int Monster_State;
	float Monster_HP;
	float Monster_Boss_2_2;
	//��
	UIProgressBar * bar;
	Sprite * Space;
	Sprite* Monster;

	Animation * animation;


	float Dir;
	bool FindTarget;
	bool Arrive;
	MoveBy* Move;
	Vec2 tileCoordForPosition(Vec2 position, TMXTiledMap *_tileMap); //���� ��ǥ Ÿ�ϸ� ���� ��ȯ
	bool propertyValue(TMXTiledMap * tileMap, Vec2 point); //���� �̵��� Ÿ�� ���� Ȯ��
	void Monster_Move(TMXTiledMap * tileMap); //Monster ���� ������

	double sinTBL[360];
	double cosTBL[360];

	void LookTarget(Sprite * Hero, bool Move, TMXTiledMap * tileMap);//�Ĵٺ���
	void Tracking(Vec2 ObjPos, Vec2 Target, TMXTiledMap * tileMap);
	void retrunPos(Vec2 Pos, TMXTiledMap * tileMap);

	float FireDelay;
	bool MonsterContainerCheck;
	BulletPosition * MonsterbulletPositon;

	//���� �Ѿ�
	Layer *Bulletlayer;
	int MonsterWeaponCode;

	bool MonsterShotCheck;
};