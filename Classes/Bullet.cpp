#include "Bullet.h"

void Bullet::update(float delta)
{
	this->setPositionX(this->getPositionX() + (dirX * BulletSpeed * delta));//2500
	this->setPositionY(this->getPositionY() + (dirY * BulletSpeed * delta));
}

Bullet * Bullet::createandinit(float Rotation, float Speed)
{
	Bullet * bullet = new Bullet();
	bullet->BulletSpeed = Speed;
	bullet->initWithSpriteFrameName("Bullet");
	bullet->dirX = sinf(CC_DEGREES_TO_RADIANS(Rotation));
	bullet->dirY = cosf(CC_DEGREES_TO_RADIANS(Rotation));
	bullet->schedule(schedule_selector(Bullet::update));
	bullet->autorelease();
	return bullet;
}