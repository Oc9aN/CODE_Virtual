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
	//바
	UIProgressBar * bar;
	Sprite * Space;
	Sprite* Monster;

	Animation * animation;


	float Dir;
	bool FindTarget;
	bool Arrive;
	MoveBy* Move;
	Vec2 tileCoordForPosition(Vec2 position, TMXTiledMap *_tileMap); //몬스터 좌표 타일맵 으로 변환
	bool propertyValue(TMXTiledMap * tileMap, Vec2 point); //몬스터 이동할 타일 정보 확인
	void Monster_Move(TMXTiledMap * tileMap); //Monster 패턴 움직임

	double sinTBL[360];
	double cosTBL[360];

	void LookTarget(Sprite * Hero, bool Move, TMXTiledMap * tileMap);//쳐다보기
	void Tracking(Vec2 ObjPos, Vec2 Target, TMXTiledMap * tileMap);
	void retrunPos(Vec2 Pos, TMXTiledMap * tileMap);

	float FireDelay;
	bool MonsterContainerCheck;
	BulletPosition * MonsterbulletPositon;

	//몬스터 총알
	Layer *Bulletlayer;
	int MonsterWeaponCode;

	bool MonsterShotCheck;
};