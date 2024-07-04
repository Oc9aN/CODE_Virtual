#include "Monster.h"

C_Monster::C_Monster(Layer * layer)
{
	MonsterWeaponCode = RandomHelper::random_int(0, 3);
	for (int i = 0; i<360; i++)
	{
		sinTBL[i] = sin(i*0.0175);
		cosTBL[i] = cos(i*0.0175);
	}
	bar = new UIProgressBar(layer);
	bar->SetBackgroundSprite(Sprite::create("UI/Bar_Background.png"));
	bar->SetForegroundSprite(Sprite::create("UI/Bar.png"));
	bar->SetScale(0.25f, 0.20f);
	
	Monster_HP = 3.0f;
	Monster_Boss_2_2 = 20.0f;

	Monster = Sprite::create(StringUtils::format("Monster/Monster_%d.png",MonsterWeaponCode));
	Monster->setScale(1.7f);
	layer->addChild(Monster, 2);
	switch (MonsterWeaponCode)
	{
	case 0:
		FireDelay = 1.0f;
		break;
	case 1:
		FireDelay = 1.0f;
		break;
	case 2:
		FireDelay = 0.3f;
		break;
	case 3:
		FireDelay = 0.1f;
		break;
	default:
		break;
	}
	MonsterContainerCheck = false;

	Space = Sprite::create();
	Space->setPosition(Vec2(Monster->getContentSize().width/2,Monster->getContentSize().height/2-6));
	Space->setRotation(Monster->getRotation());

	animation = Animation::create();

	for (int i = 0; i < 10; i++)
	{
		animation->addSpriteFrameWithFile(StringUtils::format("Monster/Monster_Move_%d.png", i));
	}

	animation->setDelayPerUnit(0.1f);
	auto animate = Animate::create(animation);
	Space->runAction(RepeatForever::create(animate));
	Monster->addChild(Space, -1);

	FindTarget = false;
	Arrive = true;
	Monster_State = LEFT;
	MonsterShotCheck = false;
}

Vec2 C_Monster::tileCoordForPosition(Vec2 position, TMXTiledMap *_tileMap)
{
	int x = position.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
	return ccp(x, y);
}

bool C_Monster::propertyValue(TMXTiledMap * tileMap,Vec2 point)
{
	auto collisionCheak = tileMap->getLayer("Way");
	
	CCPoint MonsterPos = Monster->getPosition();

	CCPoint tileCoord = this->tileCoordForPosition(MonsterPos + point, tileMap);
	int tileGid = collisionCheak->tileGIDAt(tileCoord);

	if (tileGid > 0)
		return true;
}

void C_Monster::Monster_Move(TMXTiledMap * tileMap)
{
	if (FindTarget == false)
	{
		if (Monster != nullptr)
		{
			Vec2 Mon = Monster->getPosition();
			Monster->stopAllActions();
			bool property;
			if (Monster_State == LEFT)
			{
				property = propertyValue(tileMap, Point(-25, 0));
				Monster->setRotation(-90.0f);
				if (property == true)
					Mon.x -= 5;
				else
					Monster_State = DOWN;
			}
			else if (Monster_State == DOWN)
			{
				property = propertyValue(tileMap, Point(0, -25));
				Monster->setRotation(180.0f);
				if (property == true)
					Mon.y -= 5;
				else
					Monster_State = RIGHT;
			}
			else if (Monster_State == RIGHT)
			{
				property = propertyValue(tileMap, Point(25, 0));
				Monster->setRotation(90.0f);
				if (property == true)
					Mon.x += 5;
				else
					Monster_State = UP;
			}
			else if (Monster_State == UP)
			{
				property = propertyValue(tileMap, Point(0, 25));
				Monster->setRotation(0.0f);
				if (property == true)
					Mon.y += 5;
				else
					Monster_State = LEFT;
			}
			Monster->setPosition(Mon);
		}
	}
}
void C_Monster::Tracking(Vec2 ObjPos, Vec2 Target, TMXTiledMap * tileMap)
{
	Vec2 Pos;
	int temp;

	temp = (int)((atan2(abs(ObjPos.y - Target.y), abs(ObjPos.x - Target.x))) * 180) / 3.14;

	if (Target.y - ObjPos.y > 0)
	{
		if (Target.x - ObjPos.x > 0)
			temp = temp + 90;
		else
			temp = 270 - temp;
	}
	else
	{
		if (Target.x - ObjPos.x > 0)
			temp = 90 - temp;
		else
			temp = 270 + temp;
	}

	Pos.x = sinTBL[temp] * 2;
	Pos.y = cosTBL[temp] * 2;
	auto collisionCheak = tileMap->getLayer("collisionCheak");

	CCPoint objectPos = Point(ObjPos.x + Pos.x, ObjPos.y - Pos.y);
	int x = objectPos.x / tileMap->getTileSize().width;
	int y = ((tileMap->getMapSize().height * tileMap->getTileSize().height) - objectPos.y) / tileMap->getTileSize().height;

	int tileGid = collisionCheak->tileGIDAt(Point(x, y));

	if (tileGid <= 0)
		Monster->setPosition(ObjPos.x + Pos.x, ObjPos.y - Pos.y);
}

void C_Monster::retrunPos(Vec2 Pos, TMXTiledMap * tileMap)
{
	MonsterShotCheck = false;
	float Dirx = pow(Monster->getPosition().x - Pos.x, 2); //몬스터가 도착했는지 거리재기
	float Diry = pow(Monster->getPosition().y - Pos.y, 2);
	Dir = sqrt(Dirx + Diry);
	if (Dir <= 1) //제자리에 왔다면
	{
		Arrive = true;
		FindTarget = false;
	}
	else
		Tracking(Monster->getPosition(), Pos, tileMap);
}

void C_Monster::LookTarget(Sprite * Hero, bool Move, TMXTiledMap * tileMap)
{
	if (Monster != nullptr)
	{
		MonsterShotCheck = true;
		float Dirx = pow(Monster->getPosition().x - Hero->getPosition().x, 2); //몬스터가 도착했는지 거리재기
		float Diry = pow(Monster->getPosition().y - Hero->getPosition().y, 2);
		Dir = sqrt(Dirx + Diry);
		if (Monster != nullptr)
		{
			float AngleOffset = F->GetAngleOffset(Hero->getPosition(), Monster->getPosition(), -1, 90);
			//몬스터 고개돌리기
			Monster->setRotation(AngleOffset);
			FindTarget = true;
			auto collisionCheak = tileMap->getLayer("collisionCheak");

			CCPoint objectPos = Monster->getPosition();
			int x = objectPos.x / tileMap->getTileSize().width;
			int y = ((tileMap->getMapSize().height * tileMap->getTileSize().height) - objectPos.y) / tileMap->getTileSize().height;

			int tileGid = collisionCheak->tileGIDAt(Point(x, y));

			if (Dir > 250.0f && Move == true)
			{
				Arrive = false;
				Tracking(Monster->getPosition(), Hero->getPosition(), tileMap);//플레이어 따라가기
			}
			else
				Arrive = true;
		}
	}
}