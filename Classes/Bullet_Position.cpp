#include "Bullet_Position.h"

void BulletPosition::bulletPosition(int a, Sprite * Spr, int Akimbo, bool AkimboCheak, bool Container)
{
	Vec2 HeroPosition = Spr->getPosition();
	float HeroRotation = Spr->getRotation();

	float Width, Hight;
	switch (a)
	{
	case 0://´õºí¹Ù·¿
	{
		Bullet_Damage = 1.0f;
		SimpleAudioEngine::getInstance()->playEffect("Sound/gun sound/DoubleShotgun.wav", false);
		Width = 13.0f;
		Hight = 64.0f;

		Circle = F->CircleEquation(Width, Hight, HeroRotation);
		Change_X = F->ChangeX(Width, HeroRotation);
		Change_Y = F->ChangeY(Width, HeroRotation);

		Bullet * bullet[6];
		if (Container)
			for (int i = 0; i < 6; i++)
			{
				bullet[i] = { Bullet::createandinit(HeroRotation - 25.0f + (i * ((float)50 / 6)),1800)};
				bullet[i]->setPosition(Vec2(HeroPosition.x + Circle[0] + Change_X,
					HeroPosition.y + Circle[1] + Change_Y));
				bullet[i]->setRotation(HeroRotation - 25.0f + (i * ((float)50 / 6)));
				bulletContainer.push_back(bullet[i]);//ÃÑ¾Ë ¹ÝÈ¯
				bulletLayer->addChild(bullet[i]);
			}
		else
			for (int i = 0; i < 6; i++)
			{
				bullet[i] = { Bullet::createandinit(HeroRotation - 25.0f + (i * ((float)50 / 6)),1800) };
				bullet[i]->setPosition(Vec2(HeroPosition.x + Circle[0] + Change_X,
					HeroPosition.y + Circle[1] + Change_Y));
				bullet[i]->setRotation(HeroRotation - 25.0f + (i * ((float)50 / 6)));
				MonsterbulletContainer.push_back(bullet[i]);//ÃÑ¾Ë ¹ÝÈ¯
				bulletLayer->addChild(bullet[i]);
			}
	}
	break;
	case 1://ÆßÇÁ¼¦°Ç
	{
		Bullet_Damage = 1.0f;
		SimpleAudioEngine::getInstance()->playEffect("Sound/gun sound/Pump.wav", false);
		Width = 14.0f;
		Hight = 70.0f;

		Circle = F->CircleEquation(Width, Hight, HeroRotation);
		Change_X = F->ChangeX(Width, HeroRotation);
		Change_Y = F->ChangeY(Width, HeroRotation);

		Bullet * bullet[6];
		if (Container)
			for (int i = 0; i < 6; i++)
			{
				bullet[i] = { Bullet::createandinit(HeroRotation - 25.0f + (i * ((float)50 / 6)),1800) };
				bullet[i]->setPosition(Vec2(HeroPosition.x + Circle[0] + Change_X, HeroPosition.y + Circle[1] + Change_Y));
				bullet[i]->setRotation(HeroRotation - 25.0f + (i * ((float)50 / 6)));
				bulletContainer.push_back(bullet[i]);//ÃÑ¾Ë ¹ÝÈ¯
				bulletLayer->addChild(bullet[i]);
			}
		else
			for (int i = 0; i < 6; i++)
			{
				bullet[i] = { Bullet::createandinit(HeroRotation - 25.0f + (i * ((float)50 / 6)),1800) };
				bullet[i]->setPosition(Vec2(HeroPosition.x + Circle[0] + Change_X, HeroPosition.y + Circle[1] + Change_Y));
				bullet[i]->setRotation(HeroRotation - 25.0f + (i * ((float)50 / 6)));
				MonsterbulletContainer.push_back(bullet[i]);//ÃÑ¾Ë ¹ÝÈ¯
				bulletLayer->addChild(bullet[i]);
			}
	}
	break;
	case 2://AK-47
	{
		Bullet_Damage = 1.0f;
		SimpleAudioEngine::getInstance()->playEffect("Sound/gun sound/Rifle.wav", false);
		Width = 13.0f;
		Hight = 68.0f;

		Circle = F->CircleEquation(Width, Hight, HeroRotation);
		Change_X = F->ChangeX(Width, HeroRotation);
		Change_Y = F->ChangeY(Width, HeroRotation);

		if (Container)
		{
			Bullet * bullet = Bullet::createandinit(HeroRotation, 1800);
			bullet->setPosition(Vec2(HeroPosition.x + Circle[0] + Change_X, HeroPosition.y + Circle[1] + Change_Y));
			bullet->setRotation(HeroRotation);
			bulletContainer.push_back(bullet);//ÃÑ¾Ë ¹ÝÈ¯
			bulletLayer->addChild(bullet);
		}
		else
		{
			Bullet * bullet = Bullet::createandinit(HeroRotation, 1800);
			bullet->setPosition(Vec2(HeroPosition.x + Circle[0] + Change_X, HeroPosition.y + Circle[1] + Change_Y));
			bullet->setRotation(HeroRotation);
			MonsterbulletContainer.push_back(bullet);//ÃÑ¾Ë ¹ÝÈ¯
			bulletLayer->addChild(bullet);
		}
	}
	break;
	case 3://¼­ºê¸Ó½Å°Ç
	{
		Bullet_Damage = 1.0f;
		SimpleAudioEngine::getInstance()->playEffect("Sound/gun sound/SubmachineGun.wav", false);
		
		Width = (AkimboCheak) ? 19.0f - Akimbo * 40 : 2.0f;
		Hight = 75.0f;

		Circle = F->CircleEquation(2.0f, Hight, HeroRotation);
		Change_X = F->ChangeX(Width, HeroRotation);
		Change_Y = F->ChangeY(Width, HeroRotation);

		if (Container)
		{
			Bullet * bullet = Bullet::createandinit(HeroRotation, 1800);
			bullet->setPosition(Vec2(HeroPosition.x + Circle[0] + Change_X, HeroPosition.y + Circle[1] + Change_Y));
			bullet->setRotation(HeroRotation);
			bulletContainer.push_back(bullet);//ÃÑ¾Ë ¹ÝÈ¯
			bulletLayer->addChild(bullet);
		}
		else
		{
			Bullet * bullet = Bullet::createandinit(HeroRotation, 1800);
			bullet->setPosition(Vec2(HeroPosition.x + Circle[0] + Change_X, HeroPosition.y + Circle[1] + Change_Y));
			bullet->setRotation(HeroRotation);
			MonsterbulletContainer.push_back(bullet);//ÃÑ¾Ë ¹ÝÈ¯
			bulletLayer->addChild(bullet);
		}
	}
	break;
	case 4://È­¿°¹æ»ç±â
	{
		Bullet_Damage = 0.5f;
		Width = (Container) ? 9.0f : -3.0f;
		Hight = (Container) ? 80.0f : 85.0f;

		Circle = F->CircleEquation(Width, Hight, HeroRotation);
		Change_X = F->ChangeX(Width, HeroRotation);
		Change_Y = F->ChangeY(Width, HeroRotation);

		if (Container)
		{
			Bullet * bullet = Bullet::createandinit(HeroRotation + RandomHelper::random_int(-15, 15), 500);
			auto Scale = ScaleBy::create(1.0f, 3.5);
			auto Angle = RotateBy::create(1.0f, 360);
			auto Fade = FadeOut::create(1.0f);
			auto Spawn = Spawn::create(Scale, Angle, Fade, nullptr);
			bullet->FlamethrowerCheak = true;
			bullet->runAction(Spawn);
			bullet->setTexture("Gun/Fire.png");
			bullet->setPosition(Vec2(HeroPosition.x + Circle[0] + Change_X,
				HeroPosition.y + Circle[1] + Change_Y));
			bullet->setRotation(HeroRotation);
			bulletContainer.push_back(bullet);//ÃÑ¾Ë ¹ÝÈ¯
			bulletLayer->addChild(bullet);
		}
		else
		{
			Bullet * bullet = Bullet::createandinit(HeroRotation + RandomHelper::random_int(-15, 15), 500);
			auto Scale = ScaleBy::create(1.0f, 3.5);
			auto Angle = RotateBy::create(1.0f, 360);
			auto Fade = FadeOut::create(1.0f);
			auto Spawn = Spawn::create(Scale, Angle, Fade, nullptr);
			bullet->FlamethrowerCheak = true;
			bullet->runAction(Spawn);
			bullet->setTexture("Gun/Fire.png");
			bullet->setPosition(Vec2(HeroPosition.x + Circle[0] + Change_X,
				HeroPosition.y + Circle[1] + Change_Y));
			bullet->setRotation(HeroRotation);
			MonsterbulletContainer.push_back(bullet);//ÃÑ¾Ë ¹ÝÈ¯
			bulletLayer->addChild(bullet);
		}
	}
	break;

	case 5://¹Ì»çÀÏ
	{
		SimpleAudioEngine::getInstance()->playEffect("Sound/gun sound/Launcher.wav", false);
		Bullet_Damage = 8.0f;
		Width = 17.0f;
		Hight = 70.0f;

		Circle = F->CircleEquation(Width, Hight, HeroRotation);
		Change_X = F->ChangeX(Width, HeroRotation);
		Change_Y = F->ChangeY(Width, HeroRotation);

		Bullet * bullet = Bullet::createandinit(HeroRotation, 1800);
		bullet->setTexture("Skill/Missile.png");
		bullet->setScale(2.0f);
		bullet->setPosition(Vec2(HeroPosition.x + Circle[0] + Change_X, HeroPosition.y + Circle[1] + Change_Y));
		bullet->setRotation(HeroRotation);
		bulletContainer.push_back(bullet);//ÃÑ¾Ë ¹ÝÈ¯
		bullet->setTag(a);
		bulletLayer->addChild(bullet);
	}
	break;
	case 6://deathandgun
	{
		SimpleAudioEngine::getInstance()->playEffect("Sound/gun sound/Revolver.wav", false);
		Bullet_Damage = 5.0f;
		Width = 0.0f;
		Hight = 75.0f;

		Circle = F->CircleEquation(Width, Hight, HeroRotation);
		Change_X = F->ChangeX(Width, HeroRotation);
		Change_Y = F->ChangeY(Width, HeroRotation);

		Bullet * bullet = Bullet::createandinit(HeroRotation, 1500);
		bullet->setTexture("Skill/Dead and Gun_Bullet.png");
		bullet->setScale(3.0f);
		bullet->setPosition(Vec2(HeroPosition.x + Circle[0] + Change_X, HeroPosition.y + Circle[1] + Change_Y));
		bullet->setRotation(HeroRotation);
		bulletContainer.push_back(bullet);//ÃÑ¾Ë ¹ÝÈ¯
		bullet->setTag(a);
		bulletLayer->addChild(bullet);
	}
	break;
	default://±ÇÃÑ
	{
		Bullet_Damage = 1.0f;
		SimpleAudioEngine::getInstance()->playEffect("Sound/gun sound/Pistol.wav", false);

		Width = (AkimboCheak) ? 24.0f - Akimbo * 49.0f : 0.0f;
		Hight = 68.0f;

		Circle = F->CircleEquation(Width, Hight, HeroRotation);
		Change_X = F->ChangeX(Width, HeroRotation);
		Change_Y = F->ChangeY(Width, HeroRotation);

		Bullet * bullet = Bullet::createandinit(HeroRotation, 1800);
		bullet->setPosition(Vec2(HeroPosition.x + Circle[0] + Change_X, HeroPosition.y + Circle[1] + Change_Y));
		bullet->setRotation(HeroRotation);
		bulletContainer.push_back(bullet);//ÃÑ¾Ë ¹ÝÈ¯
		bulletLayer->addChild(bullet);
	}
	break;
	}

	Change_X = F->ChangeX(Width, HeroRotation);
	Change_Y = F->ChangeY(Width, HeroRotation);

	float * Circle_Muzzle = F->CircleEquation(Width, Hight - 16.0f, HeroRotation);

	auto MuzzleFlash = Sprite::createWithSpriteFrameName(StringUtils::format("MuzzleFlash_%d", RandomHelper::random_int(0, 2)));
	MuzzleFlash->setPosition(HeroPosition.x + Circle_Muzzle[0] + Change_X, HeroPosition.y + Circle_Muzzle[1] + Change_Y);
	MuzzleFlash->setRotation(HeroRotation);
	MuzzleFlash->setScale(2.0f);
	MuzzleFlash->runAction(Sequence::create(FadeOut::create(0.01f),RemoveSelf::create(),NULL));
	bulletLayer->addChild(MuzzleFlash, 2);//ÃÑ±¸È­¿°
}

void BulletPosition::AfterEffect(Sprite * Spr)
{
	auto sprite = Sprite::createWithSpriteFrameName("Dead and Gun_Effect");
	sprite->setPosition(Spr->getPositionX(), Spr->getPositionY());
	sprite->setScale(Spr->getScaleX(),Spr->getScaleY()-1.0f);
	sprite->setOpacity(90.0f);
	sprite->runAction(Sequence::create(FadeOut::create(2.0f), RemoveSelf::create(), NULL));
	sprite->setRotation(Spr->getRotation());
	bulletLayer->addChild(sprite,-1);
}

BulletPosition::BulletPosition(Layer * layer)
{
	bulletLayer = layer;
}
