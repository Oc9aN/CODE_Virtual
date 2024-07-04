#include "Logo.h"

USING_NS_CC;

Scene* Logo::createScene()
{
	auto scene = Scene::create();
	auto layer = Logo::create();
	scene->addChild(layer);
	return scene;
}

void Logo::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	for (int x = 0; x < 2; x++)
	{
		Open_Action[x] = MoveBy::create(1.0f, Vec2(-900 + (1800 * x), 0));
		if (x == 0)
			MainMenu_Background[0]->runAction(Open_Action[x]);
		if (x == 1)
			MainMenu_Background[1]->runAction(Open_Action[x]);
	}
	Game_Name->setVisible(false);
	Play->cleanup();
	Play->setVisible(false);
	MainMenu_Background[2]->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create(CC_CALLBACK_0(Logo::ChangeScene, this)), NULL));
}

bool Logo::init()
{
	this->setKeyboardEnabled(true);

	Singleton::GetInstance()->BGM = true;
	Singleton::GetInstance()->SFX = true;

	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Sound/MainMenu (Party Hard).wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Boss/sound/MachineGun Fire&End.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Boss/sound/Laser.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Boss/sound/Boss Walk.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Boss/gun sound/Launcher.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/gun sound/DoubleShotgun.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/gun sound/Pump.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/gun sound/Rifle.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/gun sound/SubmachineGun.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/gun sound/Pistol.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/gun sound/FlameThrower.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/gun sound/Revolver.wav.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/gun sound/Launcher.wav.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/gun sound/Boom.wav.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/enemy_death/enemy_death_0.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/enemy_death/enemy_death_1.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/enemy_death/enemy_death_2.wav");


	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/MainMenu (Party Hard).wav", true);
	if (!Layer::init())
	{
		return false;
	}

	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	for (int x = 0; x < 3; x++)
	{
		SpriteFrameCache::getInstance()->addSpriteFrame(Sprite::create(StringUtils::format("Gun/MuzzleFlash_%d.png",x))->getDisplayFrame(), StringUtils::format("MuzzleFlash_%d",x));
	}
	for (int x = 0; x < 4; x++)
	{
		SpriteFrameCache::getInstance()->addSpriteFrame(Sprite::create(StringUtils::format("Boss/Boss_/boss_effect/Right_Hand_Effect_%d.png", x))->getDisplayFrame(), StringUtils::format("Right_Hand_Effect_%d", x));
	}

	SpriteFrameCache::getInstance()->addSpriteFrame(Sprite::create("Gun/Bullet.png")->getDisplayFrame(),"Bullet");
	SpriteFrameCache::getInstance()->addSpriteFrame(Sprite::create("Skill/Dead and Gun_Effect.png")->getDisplayFrame(), "Dead and Gun_Effect");

	for (int x = 0; x < 2; x++)
	{
		MainMenu_Background[x] = Sprite::create(StringUtils::format("UI/MainMenu_Background_%d.png", x));
		MainMenu_Background[x]->setPosition(Vec2(385 + (x * 515), 360));
		this->addChild(MainMenu_Background[x]);
	}

	Game_Name = Sprite::create();

	auto GameName = Animation::create();
	for (int i = 0; i < 22; i++)
	{
		GameName->addSpriteFrameWithFile(StringUtils::format("UI/Main_menu_%d.png", i));
	}
	Game_Name->setPosition(Vec2(640, 360));
	GameName->setDelayPerUnit(0.03f);
	auto GameNameAnimate = Animate::create(GameName);
	Game_Name->runAction(RepeatForever::create(Sequence::create(GameNameAnimate,DelayTime::create(3.0f),NULL)));
	this->addChild(Game_Name, 1);

	Play = Sprite::create("UI/Play.png");
	Play->setPosition(Vec2(640, 200));
	Play->runAction(RepeatForever::create(Blink::create(1.0f, 1)));
	this->addChild(Play);


	return true;
}

void Logo::ChangeScene()
{
	this->setTouchEnabled(false);
	Director::getInstance()->replaceScene(ChapterSelect::createScene());
}

bool Logo::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}

void Logo::onTouchEnded(Touch * touch, Event * event)
{
	for (int x = 0; x < 2; x++)
	{
		Open_Action[x] = MoveBy::create(1.0f, Vec2(-900 + (1800 * x), 0));
		if (x == 0)
			MainMenu_Background[0]->runAction(Open_Action[x]);
		if (x == 1)
			MainMenu_Background[1]->runAction(Open_Action[x]);
	}
	Game_Name->setVisible(false);
	Play->cleanup();
	Play->setVisible(false);
	MainMenu_Background[2]->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create(CC_CALLBACK_0(Logo::ChangeScene, this)), NULL));
}
