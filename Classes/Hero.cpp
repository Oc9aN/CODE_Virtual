#include "Hero.h"

Hero::Hero(Layer *layer)
{
	HeroImage = Sprite::create("Hero/Hero.png");
	HeroImage->setScale(1.6f);

	Space = Sprite::create();
	Space->setScale(0.95f);
	Space->setPosition(Vec2(HeroImage->getContentSize().width/2,HeroImage->getContentSize().height/2-8));

	Hero_HP = 3;
	NoDead = false;
	ShotCheck = false;
	Invincibility = false;
	HeroContainerCheck = false;
	AkimboCheak = false;
	ShieldSpace = nullptr;

	auto animation = Animation::create();
	for (int i = 0; i < 10; i++)
	{
		animation->addSpriteFrameWithFile(StringUtils::format("Hero/Hero_Move_%d.png", i));
	}
	animation->setDelayPerUnit(0.08f);
	auto animate = Animate::create(animation);
	Space->runAction(RepeatForever::create(animate));
	HeroImage->addChild(Space, -1);//히어로 다리
	layer->addChild(HeroImage,1);
}



void Hero::Shield()
{
	auto shield = Animation::create();
	for (int i = 0; i < 9; i++)
	{
		shield->addSpriteFrameWithFile(StringUtils::format("UI/Shield_%d.png", i));
	}
	ShieldSpace = Sprite::create("UI/Shield_0.png");
	ShieldSpace->setPosition(Vec2(HeroImage->getContentSize().width / 2, HeroImage->getContentSize().height / 2));
	shield->setDelayPerUnit(0.04f);

	auto shield_Animate = Animate::create(shield);
	ShieldSpace->runAction(RepeatForever::create(Sequence::create(shield_Animate,DelayTime::create(3.0f),NULL)));
	HeroImage->addChild(ShieldSpace);
}

void Hero::HeroChange(int a, bool Akimbo)
{
	switch (a)
	{
	case -1:
		HeroImage->setTexture("Hero/Hero.png");
		if (Akimbo)
			HeroImage->setTexture("Hero/Akimbo_Pistol.png");
		FireDelay = 0.5f;
		break;
	case 0:
		HeroImage->setTexture("Hero/Character_Doublebarrelshotgun.png");
		FireDelay = 1.0f;
		break;
	case 1:
		HeroImage->setTexture("Hero/Character_Pumpactionshotgun.png");
		FireDelay = 1.0f;
		break;
	case 2:
		HeroImage->setTexture("Hero/Character_AK-47.png");
		FireDelay = 0.3f;
		break;
	case 3:
		HeroImage->setTexture("Hero/Character_Uzi.png");
		if (Akimbo)
			HeroImage->setTexture("Hero/Akimbo_Uzi.png");
		FireDelay = 0.15f;
		break;
	case 4:
		HeroImage->setTexture("Hero/Character_Flamethrower.png");//화염방사기
		FireDelay = 0.001f;
		break;
	case 5:
		HeroImage->setTexture("Hero/Character_Boomer.png");//박격포
		FireDelay = 0.5f;
		break;
	case 6:
		HeroImage->setTexture("Hero/Character_Death and gun.png");//Death_And_Gun
		FireDelay = 0.5f;
		break;
	default:
		break;
	}
}