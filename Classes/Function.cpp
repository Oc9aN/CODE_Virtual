#include "Function.h"

float Function::GetAngleOffset(Vec2 Obj_1, Vec2 Obj_2, int Check, int NUM)
{
	float diffX = Obj_1.x - Obj_2.x;
	float diffY = Obj_1.y - Obj_2.y;
	float angleRadian = atan2f(diffY, diffX);
	return CC_RADIANS_TO_DEGREES(angleRadian) * (Check) + NUM;
}

bool Function::CrashRect(Sprite * Obj_1, Sprite * Obj_2)
{
	return Obj_1->getBoundingBox().intersectsRect(Obj_2->getBoundingBox());
}

bool Function::CrashPoint(Sprite * Obj_1, Vec2 Obj_2)
{
	return Obj_1->getBoundingBox().containsPoint(Obj_2);
}

float Function::Pythagoras(float x, float y)
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

float * Function::DirPos(float Rotation)
{
	static float Result[2];
	Result[0] = sinf(CC_DEGREES_TO_RADIANS(Rotation));//x
	Result[1] = cosf(CC_DEGREES_TO_RADIANS(Rotation));//y

	return Result;
}

float * Function::CircleEquation(float X, float Y, float Rotation)
{
	static float Result[2];
	Result[0] = sin(Rotation*M_PI / 180.0f)*(float)sqrt(pow(X, 2) + pow(Y, 2));
	Result[1] = cos(Rotation*M_PI / 180.0f)*(float)sqrt(pow(X, 2) + pow(Y, 2));

	return Result;
}

float Function::ChangeX(float length, float Rotation)
{
	float ChangeX = length;
	float A = length / 90.0f;

	if (Rotation < 0.0f)
		ChangeX += A*Rotation;

	if (0.0f <= Rotation&&Rotation <= 180.0f)
		ChangeX -= A*Rotation;

	if (180.0f < Rotation&&Rotation <= 270)
		ChangeX += A*(Rotation - 360.0f);
	return ChangeX;
}

float Function::ChangeY(float length, float Rotation)
{
	float ChangeY = 0.0f;
	float A = length / 90.0f;

	if (Rotation < 0)
		ChangeY += -A * Rotation;

	if (0 <= Rotation&&Rotation <= 90)
		ChangeY -= A*Rotation;

	if (90 < Rotation&&Rotation <= 270)
		ChangeY += A*(Rotation - 180);

	return ChangeY;
}

bool Function::CollisionCheak(Vec2 pos, std::string layer, Sprite * Spr, TMXTiledMap * TileMap)
{
	auto collisionCheak = TileMap->getLayer(layer);

	Vec2 objectPos = Spr->getPosition();

	Vec2 tileCoord = Vec2((pos.x + objectPos.x) / TileMap->getTileSize().width, ((TileMap->getMapSize().height * TileMap->getTileSize().height) - (pos.y + objectPos.y)) / TileMap->getTileSize().height);
	int tileGid = collisionCheak->tileGIDAt(tileCoord);

	if (tileGid > 0)
		return true;
	else
		return false;
}

Vec2 Function::FindWay(Sprite * Obj, TMXTiledMap * TileMap)
{
	int i = 1;
	Vec2 Position;
	std::string Way = "Way";
	while (1)
	{
		if (CollisionCheak(Position = Vec2(i, 0), Way, Obj, TileMap))
			break;
		else if (CollisionCheak(Position = Vec2(-i, 0), Way, Obj, TileMap))
			break;
		else if (CollisionCheak(Position = Vec2(0, i), Way, Obj, TileMap))
			break;
		else if (CollisionCheak(Position = Vec2(0, -i), Way, Obj, TileMap))
			break;
		else if (CollisionCheak(Position = Vec2(i, i), Way, Obj, TileMap))
			break;
		else if (CollisionCheak(Position = Vec2(-i, i), Way, Obj, TileMap))
			break;
		else if (CollisionCheak(Position = Vec2(i, -i), Way, Obj, TileMap))
			break;
		else if (CollisionCheak(Position = Vec2(-i, -i), Way, Obj, TileMap))
			break;
		i++;
	}
	return Obj->getPosition() + Position;
}
