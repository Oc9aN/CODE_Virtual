#include "Boss.h"
USING_NS_CC;
Boss::Boss(Layer * layer)
{
	complex = false;
	B_dead = false;
	StopRazer = false;
	CheckWall = false;
	Boss_Hp = 100.0f;
	for (int i = 0; i < 360; i++)
	{
		sinTBL[i] = sin(i*0.0175);
		cosTBL[i] = cos(i*0.0175);
	}

	for (int x = 0; x < 6; x++)
	{
		BossImage[x] = Sprite::create(StringUtils::format("Boss/Boss_/Body_0%d.png", x));
		BossImage[x]->setFlippedX(true);
		BossImage[x]->setScale(1.25f);
		switch (x)
		{
		case 0:
			BossImage[x]->setPosition(Vec2(1005, 1180));
			layer->addChild(BossImage[x]);
			break;
		case 1:
			BossImage[x]->setPosition(Vec2(-70, 80));
			BossImage[x]->setAnchorPoint(Vec2(0.4f, 1.0f));//¿À¸¥ÂÊ
			break;
		case 2:
			BossImage[x]->setPosition(Vec2(215, 90));
			BossImage[x]->setAnchorPoint(Vec2(0.6f, 1.0f));//¿ÞÂÊ
			break;
		case 3:
			BossImage[x]->setPosition(Vec2(0, 50));
			break;
		case 4:
			BossImage[x]->setPosition(Vec2(130, 50));
			break;
		case 5:
			BossImage[x]->setPosition(Vec2(BossImage[0]->getContentSize().width / 2,
				BossImage[0]->getContentSize().height / 2 - 25));
			BossImage[x]->setScale(1.25f);
			break;
		}
		if (x > 0)
			BossImage[0]->addChild(BossImage[x]);
		if (x > 2)
			BossImage[x]->setZOrder(-1);
	}
	for (int x = 0; x < 2; x++)
	{
		Space[x] = Sprite::create();
		Space[x]->setFlippedY(true);
		switch (x)
		{
		case 0:
			Space[x]->setPosition(Vec2(23, -13));
			Space[x]->setScale(1.7f);
			break;
		case 1:
			Space[x]->setPosition(Vec2(28, 140));
			Space[x]->setScale(2.0f);
			break;
		}
		BossImage[x + 1]->addChild(Space[x], -2);
	}

	count = 0;
	bulletcount = 0;
}

void Boss::Boss_SetTarget(Sprite * Spr, Layer * layer)
{
	Hero = Spr;
	Bulletlayer = layer;
}

void Boss::Missile(int chagne_P)
{
	if (chagne_P == 3)
	{
		StopRazer = true;
		HeroposMiss = Hero->getPosition();
	}
	if (start == false && B_dead != true)
	{
		auto Left_Hand = Animation::create();
		for (int x = 0; x < 3; x++)
		{
			Left_Hand->addSpriteFrameWithFile(StringUtils::format("Boss/Boss_/Boss_Animation/Left/Left_%d.png", x));
		}
		Left_Hand->setDelayPerUnit(0.2f);
		auto Left_Hand_Animate = Animate::create(Left_Hand);
		BossImage[2]->runAction(Left_Hand_Animate);

		SimpleAudioEngine::sharedEngine()->playEffect("Boss/gun sound/Launcher.wav");

		float Rotation = F->GetAngleOffset(Hero->getPosition(), BossImage[0]->convertToWorldSpace(BossImage[2]->getPosition()), -1, 90);

		Circle = F->CircleEquation(0.0f, 225.0f, Rotation);
		Change_X = F->ChangeX(0.0f, Rotation);
		Change_Y = F->ChangeY(0.0f, Rotation);

		Bullet * bossbullet = Bullet::createandinit(Rotation, 850.0f);
		bossbullet->setTag(5);
		bossbullet->setTexture("Boss/RMissile.png");
		bossbullet->setScale(2.5f);
		bossbullet->setPosition(Vec2(BossImage[0]->convertToWorldSpace(BossImage[2]->getPosition()).x + Circle[0] + Change_X, BossImage[0]->convertToWorldSpace(BossImage[2]->getPosition()).y + Circle[1] + Change_Y));
		bossbullet->setRotation(Rotation);
		BossBulletContainer.push_back(bossbullet);

		auto Left_Hand_Effect = Animation::create();

		for (int x = 0; x < 7; x++)
		{
			Left_Hand_Effect->addSpriteFrameWithFile(StringUtils::format("Boss/Boss_/boss_effect/Left_Hand_Effect_%d.png", x));
		}
		Left_Hand_Effect->setDelayPerUnit(0.1f);
		auto Left_Hand_Effect_Animate = Animate::create(Left_Hand_Effect);
		Space[1]->runAction(Left_Hand_Effect_Animate);
		Bulletlayer->addChild(bossbullet);
	}
}

void Boss::MachineGun()
{
	if (B_dead != true)
	{
		if (count == 3)
			count = 0;
		BossImage[1]->setTexture(StringUtils::format("Boss/Boss_/Boss_Animation/Right/Right_%d.png", count));
		count++;

		Space[0]->setTexture(StringUtils::format("Boss/Boss_/boss_effect/Right_Hand_Effect_%d.png", RandomHelper::random_int(0, 3)));
		Space[0]->setFlippedY(true);

		if (bulletcount % 5 == 4)
			Space[0]->setVisible(false);

		else if (bulletcount % 5 == 0)
		{
			Space[0]->setVisible(true);
			bulletcount = 0;
		}
		float Rotation = F->GetAngleOffset(Hero->getPosition(), BossImage[0]->convertToWorldSpace(BossImage[1]->getPosition()), -1, 90);
		Circle = F->CircleEquation(0.0f, 225.0f, Rotation);
		Change_X = F->ChangeX(0.0f, Rotation);
		Change_Y = F->ChangeY(0.0f, Rotation);
		if (start == false)
		{
			SimpleAudioEngine::sharedEngine()->playEffect("Boss/sound/MachineGun Fire&End.wav");
			Bullet * bossbullet = Bullet::createandinit(Rotation, 1300.0f);
			bossbullet->setScale(0.9375f);
			bossbullet->setPosition(Vec2(BossImage[0]->convertToWorldSpace(BossImage[1]->getPosition()).x + Circle[0] + Change_X, BossImage[0]->convertToWorldSpace(BossImage[1]->getPosition()).y + Circle[1] + Change_Y));
			bossbullet->setRotation(Rotation);
			BossBulletContainer.push_back(bossbullet);
			Bulletlayer->addChild(bossbullet);
		}
		bulletcount++;
	}
	else
	{
		Space[0]->setVisible(false);
	}
}

void Boss::Razer()
{
	if (B_dead != true)
	{
		StopRazer = true;
		SimpleAudioEngine::sharedEngine()->playEffect("Boss/sound/Laser.wav");
		float Rotation = F->GetAngleOffset(HeroposMiss, BossImage[0]->getPosition(), -1, 90);
		Circle = F->CircleEquation(0.0f, 0.0f, Rotation);
		Change_X = F->ChangeX(0.0f, Rotation);
		Change_Y = F->ChangeY(0.0f, Rotation);
		S_Razer = Sprite::create("Boss/Rzer.png");
		S_Razer->setAnchorPoint(Vec2(0.5f, 0.0f));
		S_Razer->setPosition(Vec2(BossImage[0]->getPosition()).x + Circle[0] + Change_X, BossImage[0]->getPosition().y + Circle[1] + Change_Y);
		S_Razer->setRotation(Rotation);
		auto razer = ScaleBy::create(0.75f, 1.0f, 10.0f);
		CallFunc * raa = CallFunc::create(CC_CALLBACK_0(Boss::deletRazer, this));
		auto seq = Sequence::create(razer, raa, nullptr);
		S_Razer->runAction(seq);
		Bulletlayer->addChild(S_Razer);
	}
}

void Boss::deletRazer()
{
	S_Razer->removeFromParent();
	StopRazer = false;
	Once = true;
}

void Boss::Limit(Sprite * obj)
{
	if (B_dead != true)
	{
		float Dirx = pow(BossImage[0]->getPosition().x - obj->getPosition().x, 2);
		float Diry = pow(BossImage[0]->getPosition().y - obj->getPosition().y, 2);
		Dir = sqrt(Dirx + Diry);
	}
}

void Boss::Checkdir(float delta)
{
	if (B_dead != true)
	{
		if (DeepCircle != true && StopRazer != true)
		{
			float angleoffset = F->GetAngleOffset(BossImage[0]->getPosition(), Hero->getPosition(), -1, 90);
			BossImage[0]->setRotation(angleoffset);
			if (Dir > 220)
			{
				float angleoffset1 = F->GetAngleOffset(BossImage[0]->convertToWorldSpace(BossImage[1]->getPosition()),
					Hero->getPosition(), -1, 90);
				BossImage[1]->setRotation(angleoffset1 - angleoffset);

				float angleoffset2 = F->GetAngleOffset(BossImage[0]->convertToWorldSpace(BossImage[2]->getPosition()),
					Hero->getPosition(), -1, 90);
				BossImage[2]->setRotation(angleoffset2 - angleoffset);
			}
		}

		if (CheckWall != true && H_W_Dir > 25 && W_W_Dir > 25)
		{
			float angleoffset4 = F->GetAngleOffset(Hero->getPosition(), BossImage[0]->getPosition(), -1, 90);
			if (Dir < 175)
			{
				complex = true;
				DeepCircle = true;
			}

			if (complex == true)
			{
				if (DeepCircle)
				{
					BossImage[0]->runAction(Sequence::create(RotateBy::create(0.35f, 360.0f), CallFunc::create(CC_CALLBACK_0(Boss::goCall, this)), NULL));
				}
				float dirX = sinf(CC_DEGREES_TO_RADIANS(angleoffset4));
				float dirY = cosf(CC_DEGREES_TO_RADIANS(angleoffset4));
				Hero->setPositionX(Hero->getPositionX() + (dirX * 900 * delta));
				Hero->setPositionY(Hero->getPositionY() + (dirY * 900 * delta));
			}

			if (Dir > 400)
			{
				complex = false;
			}
		}
	}
}

void Boss::goCall()
{
	DeepCircle = false;
}

void Boss::Tracking(Sprite* obj, Point Target, int changeP)
{
	if (B_dead != true && StopRazer != true)
	{
		Point objPos = obj->getPosition();
		int temp = (int)((atan2(abs(objPos.y - Target.y), abs(objPos.x - Target.x))) * 180) / M_PI;
		if (Target.y - objPos.y > 0)
			temp = (Target.x - objPos.x > 0) ? temp + 90 : 270 - temp;
		else
			temp = (Target.x - objPos.x > 0) ? 90 - temp : 270 + temp;

		objPos.x += sinTBL[temp] * Bospeed;
		objPos.y -= cosTBL[temp] * Bospeed;
		obj->setPosition(objPos.x, objPos.y);

		if (changeP != 1)
		{
			if (Once)
			{
				SimpleAudioEngine::sharedEngine()->playEffect("Boss/sound/Boss Walk.wav");
				auto Miss = Animation::create();
				for (int i = 0; i < 8; i++)
				{
					Miss->addSpriteFrameWithFile(StringUtils::format("Boss/Boss_/BossFeet_Animaition/Boss Move_%d.png", i));
				}
				Miss->setDelayPerUnit(0.15f);
			    Missmate = Animate::create(Miss);
				BossImage[5]->runAction(RepeatForever::create(Missmate));
				Once = false;
			}
		}
	}
	else
	{
		BossImage[5]->stopAllActions();
	}
}

void Boss::follow(float bospeed_, int changeP)
{
	if (Dir > 100)
	{
		Bospeed = bospeed_;
		Tracking(BossImage[0], Hero->getPosition(), changeP);
	}
}