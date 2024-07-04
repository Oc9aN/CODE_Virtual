#include "Weapon.h"

Weapon * Weapon::createandinit(int a)
{
	Weapon * weapon = new Weapon();
	weapon->WeaponCode = a;
	weapon->initWithFile(StringUtils::format("Gun/Weapon_0%d.png", weapon->WeaponCode));
	switch (a)
	{
	case 0:
		break;
	case 1:
		weapon->setScale(0.6f);
		break;
	case 2:
		weapon->setScale(0.75f);
		break;
	case 3:
		weapon->setScale(0.9f);
		break;
	case 4:
		weapon->setScale(0.6f);
		break;
	}
	weapon->Scale = weapon->getScale();
	auto ScaleChange = ScaleTo::create(1.0f,weapon->Scale-0.15f);
	weapon->runAction(RepeatForever::create(Spawn::create(RotateBy::create(2.0f,45.0f),Sequence::create(ScaleChange,ScaleTo::create(1.0f,weapon->Scale),NULL), NULL)));
	weapon->autorelease();
	return weapon;
}