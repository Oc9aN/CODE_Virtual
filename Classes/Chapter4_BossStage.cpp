#include "Chapter4_BossStage.h"


void InGame_Boss::goCall()
{
	hero->Invincibility = false;
	hero->HeroImage->runAction(Show::create());
}

void InGame_Boss::AkimboRemove(float dt)
{
	hero->AkimboCheak = false;
}

void InGame_Boss::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	hero->Space->resume();
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		ESC = (ESC) ? false : true;
		break;
	case EventKeyboard::KeyCode::KEY_F1:
		Singleton::GetInstance()->WeaponCode = -1;
		ui->Magazine_Num = 0;
		hero->AkimboCheak = false;
		ui->update(Singleton::GetInstance()->WeaponCode);
		break;
	case EventKeyboard::KeyCode::KEY_F2:
		Singleton::GetInstance()->WeaponCode = 0;
		hero->AkimboCheak = false;
		ui->update(Singleton::GetInstance()->WeaponCode);
		break;
	case EventKeyboard::KeyCode::KEY_F3:
		Singleton::GetInstance()->WeaponCode = 1;
		hero->AkimboCheak = false;
		ui->update(Singleton::GetInstance()->WeaponCode);
		break;
	case EventKeyboard::KeyCode::KEY_F4:
		Singleton::GetInstance()->WeaponCode = 2;
		hero->AkimboCheak = false;
		ui->update(Singleton::GetInstance()->WeaponCode);
		break;
	case EventKeyboard::KeyCode::KEY_F5:
		Singleton::GetInstance()->WeaponCode = 3;
		hero->AkimboCheak = false;
		ui->update(Singleton::GetInstance()->WeaponCode);
		break;
	case EventKeyboard::KeyCode::KEY_F6:
		Singleton::GetInstance()->WeaponCode = 4;
		hero->AkimboCheak = false;
		ui->update(Singleton::GetInstance()->WeaponCode);
		break;
	case EventKeyboard::KeyCode::KEY_F7:
		Director::getInstance()->replaceScene(InGame_Boss::createScene());
		break;
	case EventKeyboard::KeyCode::KEY_F8:
		hero->Shield();
		hero->NoDead = true;
		break;
	case EventKeyboard::KeyCode::KEY_F9:
		//총알무한
		break;
	case EventKeyboard::KeyCode::KEY_1:

		hero->AkimboCheak = true;
		break;
	case EventKeyboard::KeyCode::KEY_2:
		Singleton::GetInstance()->WeaponCode = 5;
		hero->AkimboCheak = false;
		ui->update(Singleton::GetInstance()->WeaponCode);
		break;
	case EventKeyboard::KeyCode::KEY_3:
		Singleton::GetInstance()->WeaponCode = 6;
		hero->AkimboCheak = false;
		ui->update(Singleton::GetInstance()->WeaponCode);
		break;
	case EventKeyboard::KeyCode::KEY_4:
		if (Key_4)
		{
			this->scheduleOnce(schedule_selector(InGame_Boss::Skill_4_Remove), 8.0f);
			Skill_4 = true;
			Key_4 = false;
			hero->AkimboCheak = false;
		}
		break;

	case EventKeyboard::KeyCode::KEY_W:
		UP = true;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		LEFT = true;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		DOWN = true;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		RIGHT = true;
		break;
	case EventKeyboard::KeyCode::KEY_SHIFT:
		SHIFT = true;
		break;
	case EventKeyboard::KeyCode::KEY_7:
		boss->Boss_Hp = 0;
		break;
	case EventKeyboard::KeyCode::KEY_8:
		boss->Boss_Hp = 30;
		break;
	case EventKeyboard::KeyCode::KEY_9:
		boss->Boss_Hp = 50;
		break;
	case EventKeyboard::KeyCode::KEY_0:
		boss->Boss_Hp = 80;
		break;

	}
}

void InGame_Boss::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		UP = false;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		LEFT = false;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		DOWN = false;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		RIGHT = false;
		break;
	case EventKeyboard::KeyCode::KEY_SHIFT:
		SHIFT = false;
		break;
	}
}

void InGame_Boss::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	if (Singleton::GetInstance()->WeaponCode == 4)
		FlameSound = SimpleAudioEngine::sharedEngine()->playEffect("Sound/gun sound/FlameThrower.wav");
	hero->ShotCheck = true;
}

void InGame_Boss::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	if (Singleton::GetInstance()->WeaponCode == 4)
		SimpleAudioEngine::sharedEngine()->stopEffect(FlameSound);
	hero->ShotCheck = false;
}

void InGame_Boss::onMouseMove(cocos2d::Event * event)
{
	auto mouseEvent = static_cast<EventMouse*>(event);
	Mouse_Position = mouseEvent->getLocation();

	MouseScale.x = mouseEvent->getCursorX() - 640.0f;
	MouseScale.y = mouseEvent->getCursorY() - 360.0f;

	Hero_Angle = F->GetAngleOffset(mouseEvent->getLocation(), Vec2(640, 360), 1, 90);
	if (hero->Hero_HP > 0)
		hero->HeroImage->setRotation(Hero_Angle);
}

void InGame_Boss::menuCallback(Ref * pSender)
{
	auto pTempItem = (CCMenuItem*)pSender;
	int i = pTempItem->getTag();

	switch (i)
	{
	case 1:

		break;

	case 2:
		ESC = false;
		break;

	case 3:
		Option_Layer->setPosition(Hero_Position - Point(640, 360));
		break;

	case 4:
	{
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/MainMenu (Party Hard).wav", true);
		Director::getInstance()->replaceScene(ChapterSelect::createScene());
	}
	break;

	case 5:
		Option_Layer->setPosition(Point(-10000, -10000));
		break;
	default:
		break;
	}
}

void InGame_Boss::Skill_4_Remove(float delta)
{
	Key_4 = true;
	Skill_4 = false;
	hero->Space->setPosition(Vec2(hero->HeroImage->getContentSize().width / 2 - 25, hero->HeroImage->getContentSize().height / 2 - 8));
	hero->HeroImage->stopAllActions();
	hero->HeroImage->setVisible(true);
}

Scene * InGame_Boss::createScene()
{
	auto scene = Scene::create();

	auto layer = InGame_Boss::create();

	scene->addChild(layer);

	return scene;
}


bool InGame_Boss::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->setKeyboardEnabled(true);
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);
	pattern = 0;
	changeP = 1;
	PlusMissile = 0;
	Skill_4 = false;
	Key_4 = true;
	Once = true;
	oppa = Sprite::create("Boss/Boss_/boss_effect/sd.png");
	oppa->setVisible(false);
	I = 0;

	TileMap = TMXTiledMap::create("Map/BossStage.tmx"); //맵 레이어
	this->addChild(TileMap, -1);

	BulletLayer = Layer::create();
	this->addChild(BulletLayer);

	UI_Layer = Layer::create();

	Singleton::GetInstance()->WeaponCode = -1;

	auto BulletCollision = TileMap->getLayer("BulletCollision");
	BulletCollision->setVisible(false);

	this->scheduleUpdate();

	BossLayer = Layer::create();
	BossLayer->setPosition(Vec2::ZERO);

	hero = new Hero(this);
	hero->bulletposition = new BulletPosition(BulletLayer);
	hero->HeroImage->setPosition(Vec2(1005, 270));
	ui = new UI(UI_Layer);
	this->addChild(UI_Layer, 99);
	hero->AkimboCheak = false;
	auto Mouse = EventListenerMouse::create();
	Mouse->onMouseMove = CC_CALLBACK_1(InGame_Boss::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Mouse, this);

	boss = new Boss(BossLayer);
	boss->Boss_SetTarget(hero->HeroImage, BulletLayer);
	this->addChild(BossLayer);

	bar = new UIProgressBar(UI_Layer);
	bar->SetBackgroundSprite(Sprite::create("Boss/Frontbar.png"));
	bar->backgroundSprite->setZOrder(2);
	bar->SetForegroundSprite(Sprite::create("Boss/Backbar.png"));
	bar->foregroundSprite->setZOrder(1);
	bar->foregroundSprite->setPosition(Vec2(80, 5));
	bar->SetmidgroundSprite(Sprite::create("Boss/Bottombar.png"));
	bar->midgroundSprite->setZOrder(0);
	bar->midgroundSprite->setPosition(Vec2(80, 5));
	bar->SetPosition(Vec2(255, 650));
	bar->SetScale(1.0f, 1.0f);
	UI_Layer->addChild(oppa, -1);

	Boss_guage = Label::createWithTTF(arr, "Boss/fonts/Marker Felt.ttf", 24);
	Boss_guage->setPosition(Vec2(640, 650));
	UI_Layer->addChild(Boss_guage, 5);


	PauseLayer = Layer::create();
	PauseLayer->setPosition(Vec2(-10000, -10000));
	this->addChild(PauseLayer, UI_Layer->getZOrder() + 1);

	auto Pausebackground_Light = Sprite::create("UI/Pause_Background_Light.png");
	Pausebackground_Light->setPosition(Vec2(640, 360));
	PauseLayer->addChild(Pausebackground_Light);

	auto Pausebackground = Sprite::create("UI/Pause_Background.png");
	Pausebackground->setPosition(Vec2(640, 360));
	PauseLayer->addChild(Pausebackground);

	auto Resume = MenuItemImage::create("UI/Pause_resume_off.png", "UI/Pause_resume_on.png", "UI/Pause_resume_on.png", CC_CALLBACK_1(InGame_Boss::menuCallback, this));
	Resume->setTag(2);
	auto Option = MenuItemImage::create("UI/Pause_option_off.png", "UI/Pause_option_on.png", "UI/Pause_option_on.png", CC_CALLBACK_1(InGame_Boss::menuCallback, this));
	Option->setTag(3);
	auto P_Menu = MenuItemImage::create("UI/Pause_menu_off.png", "UI/Pause_menu_on.png", "UI/Pause_menu_on.png", CC_CALLBACK_1(InGame_Boss::menuCallback, this));
	P_Menu->setTag(4);

	auto Pause_Menu = Menu::create(Resume, Option, P_Menu, NULL);
	Pause_Menu->setPosition(Vec2(640, 225));
	Pause_Menu->alignItemsVertically();
	Pause_Menu->alignItemsVerticallyWithPadding(50.f);
	PauseLayer->addChild(Pause_Menu);

	Option_Layer = Layer::create();
	Option_Layer->setPosition(Point(-10000, -10000));

	ui->Option(Option_Layer);

	auto Back = MenuItemImage::create("UI/Back_off.png", "UI/Back_on.png", "UI/Back_on.png", CC_CALLBACK_1(InGame_Boss::menuCallback, this));
	Back->setTag(5);
	auto Menu_Back = Menu::create(Back, NULL);
	Menu_Back->setPosition(Vec2(1000, 550));
	Option_Layer->addChild(Menu_Back);
	this->addChild(Option_Layer, PauseLayer->getZOrder() + 1);

	for (int i = 0; i < 8; i++)
	{
		chip[i] = Sprite::create();
		chip[i]->setScale(2.0f);
		this->addChild(chip[i], 0);
	}

	for (int x = 0; x < 4; x++)
	{
		Door[x] = Sprite::create(StringUtils::format("Map/Map/Door_%d.png", x % 2));
		Door[x]->setRotation(90.0f);
		Door[x]->setAnchorPoint(Vec2(0, 0));
		switch (x)
		{
		case 0:
			Door[x]->setPosition(Vec2(1000, 500));
			break;
		case 1:
			Door[x]->setPosition(Vec2(800, 500));
			break;
		case 2:
			Door[x]->setPosition(Vec2(1000, 1850));
			break;
		case 3:
			Door[x]->setPosition(Vec2(800, 1850));
			break;
		}
		this->addChild(Door[x], 10);
	}
	Lock = false;

	return true;
}

void InGame_Boss::update(float delta)
{
	if (Hero_Position.y >= 500 && boss->Boss_Hp > 0)
		Lock = true;
	Door_Move();
	if (Singleton::GetInstance()->WeaponCode != 4)
		SimpleAudioEngine::sharedEngine()->stopEffect(FlameSound);
	if (ui->Magazine_Num == 0)
	{
		Singleton::GetInstance()->WeaponCode = -1;
		ui->Magazine_Label->setString("8");
		ui->Magazine_Label->setRotation(90.0f);
		ui->Magazine_Label->setScale(1.3f);
		ui->Magazine_Label->setPosition(Vec2(78, 605));
	}
	else
	{
		ui->Magazine_Label->setRotation(0.0f);
		ui->Magazine_Label->setScale(1.0f);
		ui->Magazine_Label->setPosition(Vec2(70, 605));
	}


	bool Check_UP = F->CollisionCheak(Vec2(0, 25), std::string("collisionCheak"), hero->HeroImage, TileMap);
	bool Check_DONW = F->CollisionCheak(Vec2(0, -25), std::string("collisionCheak"), hero->HeroImage, TileMap);
	bool Check_LEFT = F->CollisionCheak(Vec2(-25, 0), std::string("collisionCheak"), hero->HeroImage, TileMap);
	bool Check_RIGHT = F->CollisionCheak(Vec2(25, 0), std::string("collisionCheak"), hero->HeroImage, TileMap);
	if (changeP == 4)
	{
		Check_UP = F->CollisionCheak(Vec2(0, -25), std::string("collisionCheak"), hero->HeroImage, TileMap);
		Check_DONW = F->CollisionCheak(Vec2(0, 25), std::string("collisionCheak"), hero->HeroImage, TileMap);
		Check_LEFT = F->CollisionCheak(Vec2(25, 0), std::string("collisionCheak"), hero->HeroImage, TileMap);
		Check_RIGHT = F->CollisionCheak(Vec2(-25, 0), std::string("collisionCheak"), hero->HeroImage, TileMap);
	}

	if (Check_UP || Check_DONW || Check_LEFT || Check_RIGHT)
	{
		boss->CheckWall = true;
	}

	if (Check_UP == false && Check_DONW == false && Check_LEFT == false && Check_RIGHT == false)
	{
		if (boss->CheckWall == true)
		{
			boss->CheckWall = false;
		}
	}

	if (UP == false && LEFT == false && DOWN == false && RIGHT == false)
		hero->Space->pause();

	Hero_Position = hero->HeroImage->getPosition();

	if (ESC)
	{
		Director::getInstance()->setAnimationInterval((float)1.0 / 60);
		PauseLayer->setPosition(UI_Layer->getPosition());
		boss->B_dead = true;
		BossPause = true;
	}
	else
	{
		if (BossPause && boss->BossImage[0] != nullptr)
		{
			boss->B_dead = false;
			BossPause = false;
		}
		PauseLayer->setPosition(Vec2(-10000, -10000));
		if (Lock == false)
		{
			if (UP&&Check_UP != true && SHIFT != true)
				Hero_Position.y += 8;
		}
		else if (UP&&Check_UP != true && Hero_Position.y <= 1750 && SHIFT != true)
		{
			if (changeP == 4 && Hero_Position.y >= 550)
			{
				Hero_Position.y -= 8;
			}
			else
				Hero_Position.y += 8;
		}
		if (LEFT&&Check_LEFT != true && SHIFT != true)
		{
			if (changeP == 4)
			{
				Hero_Position.x += 8;
			}
			else
				Hero_Position.x -= 8;
		}
		if (Lock == false)
		{
			if (DOWN&&Check_DONW != true && SHIFT != true)
				Hero_Position.y -= 8;
		}
		else if (DOWN&&Check_DONW != true && Hero_Position.y >= 550 && SHIFT != true)
		{
			if (changeP == 4 && Hero_Position.y <= 1750)
			{
				Hero_Position.y += 8;
			}
			else
				Hero_Position.y -= 8;
		}
		if (RIGHT&&Check_RIGHT != true && SHIFT != true)
		{
			if (changeP == 4)
			{
				Hero_Position.x -= 8;
			}
			else
				Hero_Position.x += 8;
		}
	}

	boss->H_W_Dir = abs((1750 - hero->HeroImage->getPosition().y));
	boss->W_W_Dir = abs((550 - hero->HeroImage->getPosition().y));
	hero->HeroImage->setPosition(Hero_Position);

	switch (Singleton::GetInstance()->ClearMode)
	{
	case 0:
		Director::getInstance()->replaceScene(InGame_Boss::createScene());
		break;
	case 1:
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/MainMenu (Party Hard).wav", true);
		Director::getInstance()->replaceScene(ChapterSelect::createScene());
		break;
	default:
		break;
	}


	ui->Hero_Update(hero->Hero_HP);

	if (SHIFT == true)
	{
		this->setTouchEnabled(false);
		if (F->Pythagoras(Hero_Position.x - Mouse_Position.x, Hero_Position.y - Mouse_Position.y) > 150)
		{
			hero->ShotCheck = false;
			Vec2 Camera_Position = Camera::getDefaultCamera()->getPosition();
			hero->Space->pause();
			Camera_Position.x += MouseScale.x*0.7f * delta;
			Camera_Position.y += MouseScale.y*0.7f * delta;

			Camera::getDefaultCamera()->setPosition(Camera_Position);
			UI_Layer->setPosition(Vec2(Camera_Position.x - 640, Camera_Position.y - 360));
		}
	}
	else
	{
		if (hero->Hero_HP > 0)
		{
			this->setTouchEnabled(true);
			UI_Layer->setPosition(Vec2(Hero_Position.x - 640, Hero_Position.y - 360));
			Camera::getDefaultCamera()->setPosition(Hero_Position);
		}
	}
	MonsterCrash();
	HeroCrash();

	if (F->CollisionCheak(Point(0, 0), std::string("Exit"), hero->HeroImage, TileMap))
	{
		if (Once)
		{
			boss->B_dead = true;
			this->setTouchEnabled(false);
			this->setKeyboardEnabled(false);
			ui->LifeImageCheck(1);
			hero->ShotCheck = false;
			UP = false;
			DOWN = false;
			LEFT = false;
			RIGHT = false;
			ui->Clear = true;
			Once = false;
		}
	}

	this->scheduleOnce(schedule_selector(InGame_Boss::FireCheck), hero->FireDelay);
	if (Singleton::GetInstance()->WeaponCode == 4)
	{
		ui->bar->backgroundSprite->setVisible(true);
		ui->bar->foregroundSprite->setVisible(true);
		ui->Magazine->setVisible(false);
		ui->bar->SetPercentage(ui->Magazine_Num / 100.0f);
	}
	else
	{
		ui->bar->backgroundSprite->setVisible(false);
		ui->bar->foregroundSprite->setVisible(false);
		ui->Magazine->setVisible(true);
	}

	if (Skill_4 != true)
		hero->HeroChange(Singleton::GetInstance()->WeaponCode, hero->AkimboCheak);

	if (boss->B_dead != true)
	{
		boss->Checkdir(delta);
		boss->follow(Bospeed, changeP);
		boss->Limit(hero->HeroImage);
		/////////////////////여기서 부터 패턴
		static int Mbulletnum;
		static int Missilenum;
		static float BossMissileduration;
		static float Bossbullet_speed;
		static float Bossbullet_count = 9;
		static float Bossbullet_duration;
		if (hero->Hero_HP > 0)
		{
			if (pattern < Mbulletnum)//기관총발사   
			{
				this->schedule(schedule_selector(InGame_Boss::Fire_MushineGun_Check), Bossbullet_speed, Bossbullet_count, Bossbullet_duration);
			}
			if (pattern > Mbulletnum)//기관총발사후 미사일발사
			{
				this->schedule(schedule_selector(InGame_Boss::Fire_Missile_Check), 0.3f, Missilenum, BossMissileduration);
				if (changeP == 3)
				{
					this->scheduleOnce(schedule_selector(InGame_Boss::Fire_Razer), 2.0f);
				}
			}
		}

		if (pattern == 0)
		{
			if (boss->Boss_Hp <= 100 && boss->Boss_Hp > 80)
			{
				changeP = 1;
				Bossbullet_speed = 0.1f;
				Bossbullet_duration = 1.0f;
				BossMissileduration = 1.5f;
				Mbulletnum = 19;
				Missilenum = 0;
			}
			if (boss->Boss_Hp <= 80 && boss->Boss_Hp > 50)
			{
				changeP = 2;
				BossMissileduration = 1.5f;
				Bossbullet_duration = 1.0f;
				Bospeed = 1.0f;
				Mbulletnum = 49;
				Missilenum = 2;
			}
			if (boss->Boss_Hp <= 50 && boss->Boss_Hp > 30)
			{
				changeP = 3;
				BossMissileduration = 1.5f;
				Bossbullet_duration = 1.3f;
				Bospeed = 2.0f;
				Mbulletnum = 39;
				Missilenum = 0;
			}
			if (boss->Boss_Hp <= 30 && boss->Boss_Hp > 10)
			{
				changeP = 4;
				BossMissileduration = 1.5f;
				Bospeed = 2.0f;
				Mbulletnum = 19;
				Missilenum = 0;
			}
		}
		if (boss->Boss_Hp <= 0)
		{
			changeP = 5;
			boss->B_dead = true;
			SimpleAudioEngine::sharedEngine()->stopAllEffects();
			boss->BossImage[5]->stopAllActions();
			Bosspos = boss->BossImage[0]->getPosition();
			this->schedule(schedule_selector(InGame_Boss::Boss_Dead), 0.24f);
			static bool ddsound = true;
			if (ddsound)
			{
				SimpleAudioEngine::sharedEngine()->playEffect("Sound/boss_explosion.wav");
				ddsound = false;
			}
		}
	}

	static int oopa = 0;
	if (I > 8 && oppa != nullptr)
	{
		oppa->setPosition(640, 360);
		oppa->setOpacity(255 - oopa);
		if (255 - oopa > 242)
		{
			oopa += 1;
		}
		else
		{
			F_chip();
			oopa += 3;
		}
		oppa->setVisible(true);
		if (oopa > 250)
		{
			oppa->removeFromParent();
			oppa = nullptr;
		}
		if (boss->BossImage[0] != nullptr)
		{
			boss->BossImage[0]->removeFromParent();
			boss->BossImage[0] = nullptr;
		}
	}

}

void InGame_Boss::Door_Move()
{
	static bool opencheak = false;
	std::string open = "open"; //첫번째문
	bool cheak = F->CollisionCheak(Vec2(0, 0), open, hero->HeroImage, TileMap);
	auto Door_Move1 = MoveBy::create(0.3f, Vec2(150, 0));
	auto Door_Move2 = MoveBy::create(0.3f, Vec2(-150, 0));
	if (cheak == true && opencheak == false)
	{
		boss->start = false;
		Door[0]->runAction(Door_Move1);
		Door[1]->runAction(Door_Move2);
		opencheak = true;
	}
	else if (cheak == false && opencheak == true)
	{
		Door[0]->runAction(Door_Move1->reverse());
		Door[1]->runAction(Door_Move2->reverse());
		opencheak = false;
	}
}

void InGame_Boss::FireCheck(float delta)
{
	if (hero->ShotCheck)
	{
		if (hero->AkimboCheak)
		{
			if (Change == 0)
				Change = 1;
			else
				Change = 0;
		}
		else
			Change = 0;

		if (ui->Clear != true)
		{
			hero->bulletposition->bulletPosition(Singleton::GetInstance()->WeaponCode, hero->HeroImage, Change, hero->AkimboCheak, true);
			ui->Magazine_Animation();
		}
		if (ui->Magazine_Num > 0)
		{
			ui->Magazine_Num--;
			ui->Magazine_Label->setString(StringUtils::format("%d", ui->Magazine_Num));
		}
		hero->HeroContainerCheck = true;
	}
}

void InGame_Boss::MonsterCrash()
{
	for (Sprite *v : boss->BossBulletContainer)
	{
		if (F->CrashRect(hero->HeroImage, v))
		{
			if (hero->Invincibility == false)
			{
				if (hero->Hero_HP > 0)
				{
					if (hero->NoDead != true)
					{
						hero->HeroImage->runAction(Sequence::create(Blink::create(2.5f, 9), CallFunc::create(CC_CALLBACK_0(InGame_Boss::goCall, this)), NULL));
						hero->Hero_HP--;
					}
				}
				static bool Once2 = true;
				if (hero->Hero_HP <= 0 && Once2)
				{
					this->setTouchEnabled(false);
					this->setKeyboardEnabled(false);
					ui->LifeImageCheck(0);
					hero->ShotCheck = false;
					UP = false;
					DOWN = false;
					LEFT = false;
					RIGHT = false;
					Once2 = false;
				}
			}
			hero->Invincibility = true;
			if (v->getTag() == 5)
			{
				SimpleAudioEngine::getInstance()->playEffect("Sound/gun sound/Boom.wav", false);
				auto animation = Animation::create();
				for (int i = 0; i < 6; i++)
				{
					animation->addSpriteFrameWithFile(StringUtils::format("Skill/Missile_MuzzleFlash_%d.png", i));
				}
				animation->setDelayPerUnit(0.05f);
				auto animate = Animate::create(animation);
				auto Space = Sprite::create();
				Space->setPosition(v->getPosition());
				Space->runAction(Sequence::create(animate, RemoveSelf::create(), NULL));
				BulletLayer->addChild(Space);
			}
			v->setTag(1);
		}
	}
	for (auto check = boss->BossBulletContainer.begin(); check != boss->BossBulletContainer.end();)
	{
		Sprite *v = (*check);
		bool Cheak = F->CollisionCheak(Vec2(0, 0), std::string("BulletCollision"), v, TileMap);

		if (Cheak
			|| v->getTag() == 1)
		{
			if (v->getTag() == 5)
			{
				SimpleAudioEngine::getInstance()->playEffect("Sound/gun sound/Boom.wav", false);
				auto animation = Animation::create();
				for (int i = 0; i < 6; i++)
				{
					animation->addSpriteFrameWithFile(StringUtils::format("Skill/Missile_MuzzleFlash_%d.png", i));
				}
				animation->setDelayPerUnit(0.05f);
				auto animate = Animate::create(animation);
				auto Space = Sprite::create();
				Space->setPosition(v->getPosition());
				Space->runAction(Sequence::create(animate, RemoveSelf::create(), NULL));
				BulletLayer->addChild(Space);

				v->removeFromParent();
				check = boss->BossBulletContainer.erase(check);
			}
			else
			{
				v->removeFromParent();
				check = boss->BossBulletContainer.erase(check);
			}
		}
		else
		{
			++check;
		}


	}
}

void InGame_Boss::HeroCrash()
{
	if (hero->HeroContainerCheck)
	{
		for (Sprite * v : hero->bulletposition->bulletContainer)
		{
			if (v != nullptr)
			{
				if (v->getTag() == 6)
					hero->bulletposition->AfterEffect(v);
			}
		}

		for (Sprite * v : hero->bulletposition->bulletContainer)
		{
			if (boss->BossImage[0] != nullptr)
			{
				if (F->CrashRect(boss->BossImage[0], v))
				{
					if (boss->Boss_Hp > 0)
					{
						boss->Boss_Hp -= hero->bulletposition->Bullet_Damage;
					}
					if (boss->Boss_Hp <= 0 && bar->foregroundSprite != nullptr)
					{
						bar->foregroundSprite->removeFromParent();
						bar->foregroundSprite = nullptr;
					}
					if (v->getTag() == 5)
					{
						SimpleAudioEngine::getInstance()->playEffect("Sound/gun sound/Boom.wav", false);
						auto animation = Animation::create();
						for (int i = 0; i < 6; i++)
						{
							animation->addSpriteFrameWithFile(StringUtils::format("Skill/Missile_MuzzleFlash_%d.png", i));
						}
						animation->setDelayPerUnit(0.05f);
						auto animate = Animate::create(animation);
						auto Space = Sprite::create();
						Space->setPosition(v->getPosition());
						Space->runAction(Sequence::create(animate, RemoveSelf::create(), NULL));
						BulletLayer->addChild(Space);
					}
					v->setTag(1);
				}
			}
		}

		for (auto ang = hero->bulletposition->bulletContainer.begin(); ang != hero->bulletposition->bulletContainer.end();)
		{
			Sprite * v = (*ang);
			Vec2 vpos = v->getPosition();
			bool Cheak = F->CollisionCheak(Vec2(0, 0), std::string("BulletCollision"), v, TileMap);
			if (v->getTag() == 1 || Cheak
				|| vpos.x<UI_Layer->getPositionX()
				|| vpos.x>UI_Layer->getPositionX() + 1280.0f
				|| vpos.y<UI_Layer->getPositionY()
				|| vpos.y>UI_Layer->getPositionY() + 720.0f)
			{
				if (v->getTag() == 5)
				{
					SimpleAudioEngine::getInstance()->playEffect("Sound/gun sound/Boom.wav", false);
					auto animation = Animation::create();
					for (int i = 0; i < 6; i++)
					{
						animation->addSpriteFrameWithFile(StringUtils::format("Skill/Missile_MuzzleFlash_%d.png", i));
					}
					animation->setDelayPerUnit(0.05f);
					auto animate = Animate::create(animation);
					auto Space = Sprite::create();
					Space->setPosition(v->getPosition());
					Space->runAction(Sequence::create(animate, RemoveSelf::create(), NULL));
					BulletLayer->addChild(Space);

					v->removeFromParent();
					ang = hero->bulletposition->bulletContainer.erase(ang);
				}
				else
				{
					v->removeFromParent();
					ang = hero->bulletposition->bulletContainer.erase(ang);

				}
			}
			else
				++ang;
		}
	}

	bar->SetPercentage(boss->Boss_Hp / 100.0f);
}

void InGame_Boss::Fire_Missile_Check(float delta)
{
	boss->Missile(changeP);
	if (changeP != 2)
	{
		pattern = 0;
	}
	else
	{
		PlusMissile++;
		if (PlusMissile == 3)
		{
			pattern = 0;
			PlusMissile = 0;
		}
	}
}

void InGame_Boss::Fire_MushineGun_Check(float delta)
{
	pattern++;
	boss->MachineGun();
}

void InGame_Boss::Fire_Razer(float delta)
{
	Bospeed = 0.0f;
	boss->Razer();
}

void InGame_Boss::Boss_Dead(float dt)
{
	if (I < 10)
	{
		D_bosspos[I] = Sprite::create();
		D_bosspos[I]->setScale(3.0f);
		D_bosspos[I]->setPosition(Vec2((Bosspos.x - 200 + RandomHelper::random_int(0, 400)),
			(Bosspos.y - 150 + RandomHelper::random_int(0, 300))));
		this->addChild(D_bosspos[I], 10);
		static bool dead_ani[10];
		dead_ani[I] = true;
		if (dead_ani[I])
		{
			auto Die = Animation::create();
			for (int i = 1; i < 9; i++)
			{
				char str[100] = { 0 };
				sprintf(str, "Boss/Boss_/boss_effect/1-%d.png", i);
				Die->addSpriteFrameWithFile(str);
			}
			Die->setDelayPerUnit(0.15f);
			auto Diemate = Animate::create(Die);
			D_bosspos[I]->runAction(Diemate);
			dead_ani[I] = false;
		}
		I++;
	}
}

void InGame_Boss::F_chip()
{
	static bool Oncee = true;
	if (Oncee)
	{
		Lock = false;
		Door[2]->runAction(MoveBy::create(0.3f, Vec2(200, 0)));
		Door[3]->runAction(MoveBy::create(0.3f, Vec2(-200, 0)));
		for (int i = 0; i < 8; i++)
		{
			chip[i]->setPosition(Bosspos);
			auto chip_M = MoveBy::create(0.5f, Point(RandomHelper::random_int(-720, 720),
				RandomHelper::random_int(-520, 520)));
			chip[i]->runAction(chip_M);
		}

		auto A = Animation::create();
		for (int i = 1; i < 5; i++)
		{
			char str[100] = { 0 };
			sprintf(str, "Boss/Boss_/Boss_Die/Boss_Death_1_%d.png", i);
			A->addSpriteFrameWithFile(str);
		}
		A->setDelayPerUnit(0.1f);
		for (int i = 0; i < 3; i++)
		{
			Aniamate[i] = Animate::create(A);
			chip[i]->runAction(Aniamate[i]);
		}
		//
		auto B = Animation::create();
		for (int i = 1; i < 7; i++)
		{
			char str[100] = { 0 };
			sprintf(str, "Boss/Boss_/Boss_Die/Boss_Death_2_%d.png", i);
			B->addSpriteFrameWithFile(str);
		}
		B->setDelayPerUnit(0.1f);
		for (int i = 3; i < 6; i++)
		{
			Aniamate[i] = Animate::create(B);
			chip[i]->runAction(Aniamate[i]);
		}
		//
		auto C = Animation::create();
		for (int i = 1; i < 5; i++)
		{
			char str[100] = { 0 };
			sprintf(str, "Boss/Boss_/Boss_Die/Boss_Death_3_%d.png", i);
			C->addSpriteFrameWithFile(str);
		}
		C->setDelayPerUnit(0.1f);
		for (int i = 6; i < 8; i++)
		{
			Aniamate[i] = Animate::create(C);
			chip[i]->runAction(Aniamate[i]);
		}
		Oncee = false;
	}
}