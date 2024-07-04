#include "Credit.h"

Scene * Credit::createScene()
{
	auto scene = Scene::create();

	auto layer = Credit::create();

	scene->addChild(layer);

	return scene;
}

bool Credit::init()
{
	if (!Layer::init())
	{
		return false;
	}
	MainCenter = Vec2(640, 360);

	auto InAction = FadeIn::create(1.5f);
	auto OutAction = FadeOut::create(1.5f);

	Name[0] = Label::createWithTTF("DIRECTOR jeong yoon je", "UI/Blox2.ttf", 60);
	Name[1] = Label::createWithTTF("GRAPHIC kim do kyeong", "UI/Blox2.ttf", 60);
	Name[2] = Label::createWithTTF("PROGRAMING kim ji hoon", "UI/Blox2.ttf", 60);
	Name[3] = Label::createWithTTF("PROGRAMING oh si hyeon", "UI/Blox2.ttf", 60);
	Name[4] = Label::createWithTTF("PROGRAMING park sun joon", "UI/Blox2.ttf", 60);
	Name[5] = Label::createWithTTF("PROGRAMING kim chan min", "UI/Blox2.ttf", 60);
	

	for (int x = 0; x < 6; x++)
	{
		Name[x]->setPosition(MainCenter);
		Name[x]->setOpacity(0.0f);
		Name[x]->runAction(Sequence::create(DelayTime::create(0.5f+(x*3.0f)), InAction, OutAction, NULL));
		this->addChild(Name[x]);
	}
	auto LastCredit = Sprite::create("UI/Credit.png");
	LastCredit->setPosition(MainCenter);
	LastCredit->setOpacity(0.0f);
	LastCredit->runAction(Sequence::create(DelayTime::create(19.0f), InAction,NULL));
	this->addChild(LastCredit);

	return true;
}
