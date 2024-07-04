#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Function : public Layer
{
public:
	float GetAngleOffset(Vec2 Obj_1, Vec2 Obj_2, int Check, int NUM);//�߻� ����
	bool CrashRect(Sprite * Obj_1, Sprite * Obj_2);//Rect�浹
	bool CrashPoint(Sprite * Obj_1, Vec2 Obj_2);//Point�浹
	float Pythagoras(float x, float y);//��Ÿ����� ����
	float * DirPos(float Rotation);//�Ѿ� ��ġ ������

	float * CircleEquation(float X, float Y, float Rotation);
	float ChangeX(float length, float Rotation);
	float ChangeY(float length, float Rotation);//���� ������

	bool CollisionCheak(Vec2 pos, std::string layer, Sprite* Spr, TMXTiledMap * TileMap);//�� �浹
	Vec2 FindWay(Sprite * Obj, TMXTiledMap * TileMap);
};