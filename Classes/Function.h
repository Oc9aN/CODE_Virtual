#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Function : public Layer
{
public:
	float GetAngleOffset(Vec2 Obj_1, Vec2 Obj_2, int Check, int NUM);//발사 각도
	bool CrashRect(Sprite * Obj_1, Sprite * Obj_2);//Rect충돌
	bool CrashPoint(Sprite * Obj_1, Vec2 Obj_2);//Point충돌
	float Pythagoras(float x, float y);//피타고라스의 정리
	float * DirPos(float Rotation);//총알 위치 증가식

	float * CircleEquation(float X, float Y, float Rotation);
	float ChangeX(float length, float Rotation);
	float ChangeY(float length, float Rotation);//원의 방정식

	bool CollisionCheak(Vec2 pos, std::string layer, Sprite* Spr, TMXTiledMap * TileMap);//맵 충돌
	Vec2 FindWay(Sprite * Obj, TMXTiledMap * TileMap);
};