#include "Chapter2_2_InGame.h"

void InGame_Chapter_2_2::AkimboRemove(float dt)
{
	hero->AkimboCheak = false;
}

void InGame_Chapter_2_2::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
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
		Director::getInstance()->replaceScene(InGame_Chapter_2_2::createScene());
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
		this->scheduleOnce(schedule_selector(InGame_Chapter_2_2::AkimboRemove), 5.0f);
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
			this->scheduleOnce(schedule_selector(InGame_Chapter_2_2::Skill_4_Remove), 8.0f);
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
	case EventKeyboard::KeyCode::KEY_F:
		Key_F = true;
		break;
	}
}

void InGame_Chapter_2_2::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
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
	case EventKeyboard::KeyCode::KEY_F:
		Key_F = false;
		break;
	}
}

void InGame_Chapter_2_2::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	if (Singleton::GetInstance()->WeaponCode == 4)
		FlameSound = SimpleAudioEngine::sharedEngine()->playEffect("Sound/gun sound/FlameThrower.wav");
	hero->ShotCheck = true;
}

void InGame_Chapter_2_2::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
{
	if (Singleton::GetInstance()->WeaponCode == 4)
		SimpleAudioEngine::sharedEngine()->stopEffect(FlameSound);
	hero->ShotCheck = false;
}

void InGame_Chapter_2_2::onMouseMove(cocos2d::Event * event)
{
	auto mouseEvent = static_cast<EventMouse*>(event);
	Mouse_Position = mouseEvent->getLocation();

	MouseScale.x = mouseEvent->getCursorX() - 640.0f;
	MouseScale.y = mouseEvent->getCursorY() - 360.0f;

	Hero_Angle = F->GetAngleOffset(mouseEvent->getLocation(), Vec2(640, 360), 1, 90);
	if(hero->Hero_HP>0&&ui->Clear!=true && SHIFT != true)
	hero->HeroImage->setRotation(Hero_Angle);

}

void InGame_Chapter_2_2::Skill_4_Remove(float delta)
{
	Key_4 = true;
	Skill_4 = false;
	hero->Space->setPosition(Vec2(hero->HeroImage->getContentSize().width / 2 - 25, hero->HeroImage->getContentSize().height / 2 - 8));
	hero->HeroImage->stopAllActions();
	hero->HeroImage->setVisible(true);
}

Scene * InGame_Chapter_2_2::createScene()
{
	auto scene = Scene::create();

	auto layer = InGame_Chapter_2_2::create();

	scene->addChild(layer);

	return scene;
}

bool InGame_Chapter_2_2::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->setKeyboardEnabled(true);
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);

	TileMap = TMXTiledMap::create("Map/Stage2_2.tmx"); //맵 레이어
	this->addChild(TileMap);

	Once = true;
	Once2 = true;
	Key_4 = true;
	Key_F = false;
	Skill_4 = false;

	BulletLayer = Layer::create();
	this->addChild(BulletLayer);

	UI_Layer = Layer::create();

	Singleton::GetInstance()->WeaponCode = -1;

	auto BulletCollision = TileMap->getLayer("BulletCollision");
	BulletCollision->setVisible(false);

	this->scheduleUpdate();

	MonsterLayer = Layer::create();
	this->addChild(MonsterLayer);

	hero = new Hero(this);
	hero->HeroImage->setPosition(Vec2(1250, 200));
	hero->bulletposition = new BulletPosition(BulletLayer);
	
	ui = new UI(UI_Layer);
	this->addChild(UI_Layer, 99);

	PauseLayer = Layer::create();
	PauseLayer->setPosition(Vec2(-10000, -10000));
	this->addChild(PauseLayer, UI_Layer->getZOrder() + 1);

	auto Mouse = EventListenerMouse::create();
	Mouse->onMouseMove = CC_CALLBACK_1(InGame_Chapter_2_2::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Mouse, this);

	auto Pausebackground_Light = Sprite::create("UI/Pause_Background_Light.png");
	Pausebackground_Light->setPosition(Vec2(640, 360));
	PauseLayer->addChild(Pausebackground_Light);

	auto Pausebackground = Sprite::create("UI/Pause_Background.png");
	Pausebackground->setPosition(Vec2(640, 360));
	PauseLayer->addChild(Pausebackground);

	auto Resume = MenuItemImage::create("UI/Pause_resume_off.png", "UI/Pause_resume_on.png", "UI/Pause_resume_on.png", CC_CALLBACK_1(InGame_Chapter_2_2::menuCallback, this));
	Resume->setTag(2);
	auto Option = MenuItemImage::create("UI/Pause_option_off.png", "UI/Pause_option_on.png", "UI/Pause_option_on.png", CC_CALLBACK_1(InGame_Chapter_2_2::menuCallback, this));
	Option->setTag(3);
	auto P_Menu = MenuItemImage::create("UI/Pause_menu_off.png", "UI/Pause_menu_on.png", "UI/Pause_menu_on.png", CC_CALLBACK_1(InGame_Chapter_2_2::menuCallback, this));
	P_Menu->setTag(4);

	auto Pause_Menu = Menu::create(Resume, Option, P_Menu, NULL);
	Pause_Menu->setPosition(Vec2(640, 225));
	Pause_Menu->alignItemsVertically();
	Pause_Menu->alignItemsVerticallyWithPadding(50.f);
	PauseLayer->addChild(Pause_Menu);

	Monster = new C_Monster(MonsterLayer);
	Monster->MonsterbulletPositon = new BulletPosition(BulletLayer);
	Monster->Monster->setTexture("Monster/Powerful Enemy/Powerful_Enemy.png");
	Monster->Monster->setPosition(600, 1400);
	Monster->MonsterWeaponCode = 4;

	Monster->Space->removeFromParent();
	
	auto animation = Animation::create();
	for (int x = 0; x < 6; x++)
	{
		animation->addSpriteFrameWithFile(StringUtils::format("Monster/PowerfulEnemy/Powerful_Enemy_Leg_%d.png", x));
	}
	animation->setDelayPerUnit(0.2f);
	auto animate = Animate::create(animation);
	Monster->Space->runAction(RepeatForever::create(animate));
	Monster->Space->setScale(1.2f);
	Monster->Space->setPosition(Vec2(Monster->getContentSize().width / 2 + 40, Monster->getContentSize().height / 2 + 40));
	Monster->Monster->addChild(Monster->Space);
	
	Monster->MonsterContainerCheck = false;

	for (int x = 0; x < 2; x++)
	{
		Door[x] = Sprite::create(StringUtils::format("Map/Map/Door_%d.png", x % 2));
		Door[x]->setRotation(90.0f);
		Door[x]->setAnchorPoint(Vec2(0, 0));
		switch (x)
		{
		case 0:
			Door[x]->setPosition(Vec2(600, 1000));
			break;
		case 1:
			Door[x]->setPosition(Vec2(400, 1000));
			break;
		}
		this->addChild(Door[x]);
	}

	OpenCheak1 = false; //첫번째문

	OpenCheak2 = false; //두번째문

	for (int i = 0; i < 2; i++)
	{
		elevatordoor[i] = Sprite::create(StringUtils::format("Map/Map/object/elevator_door_%d.png", i + 1));
		switch (i)
		{
		case 0:
			elevatordoor[i]->setPosition(Point(550, 1762.5));
			break;
		case 1:
			elevatordoor[i]->setPosition(Point(650, 1762.5));
			break;
		}
		this->addChild(elevatordoor[i], 5);
	}

	return true;
}

void InGame_Chapter_2_2::update(float delta)
{
	if (Hero_Position.y >= 1000 && Monster->Monster_Boss_2_2 > 0)
		Lock = true;
	if (Singleton::GetInstance()->WeaponCode != 4)
		SimpleAudioEngine::sharedEngine()->stopEffect(FlameSound);
	if(Monster->Monster!=nullptr) 
	Monster->bar->SetPosition(Vec2(Monster->Monster->getPosition().x - 50, Monster->Monster->getPosition().y - 117));

	Door_Move();
	RadarMonsterCheak();
	ui->Hero_Update(hero->Hero_HP);

	bool Check_UP = F->CollisionCheak(Vec2(0, 25), std::string("collisionCheak"), hero->HeroImage, TileMap);
	bool Check_DONW = F->CollisionCheak(Vec2(0, -25), std::string("collisionCheak"), hero->HeroImage, TileMap);
	bool Check_LEFT = F->CollisionCheak(Vec2(-25, 0), std::string("collisionCheak"), hero->HeroImage, TileMap);
	bool Check_RIGHT = F->CollisionCheak(Vec2(25, 0), std::string("collisionCheak"), hero->HeroImage, TileMap);

	Hero_Position = hero->HeroImage->getPosition();

	if (UP == false && LEFT == false && DOWN == false && RIGHT == false)
		hero->Space->pause();

	if (ESC)
	{
		Director::getInstance()->setAnimationInterval((float)1.0 / 60);
		PauseLayer->setPosition(UI_Layer->getPosition());
	}
	else
	{
		PauseLayer->setPosition(Vec2(-10000, -10000));
		if (Lock == false)
		{
			if (UP&&Check_UP != true && SHIFT != true)
				Hero_Position.y += 8;
		}
		else if (UP&&Check_UP != true && Hero_Position.y <= 1700 && SHIFT != true)
			Hero_Position.y += 8;
		if (LEFT&&Check_LEFT != true && SHIFT != true)
			Hero_Position.x -= 8;
		if (Lock == false)
		{
			if (DOWN&&Check_DONW != true && SHIFT != true)
				Hero_Position.y -= 8;
		}
		else
			if (DOWN&&Check_DONW != true && Hero_Position.y >= 1050 && SHIFT != true)
				Hero_Position.y -= 8;
		if (RIGHT&&Check_RIGHT != true && SHIFT != true)
			Hero_Position.x += 8;
	}

	hero->HeroImage->setPosition(Hero_Position);

	if (SHIFT == true)
	{
		if (F->Pythagoras(Hero_Position.x - Mouse_Position.x, Hero_Position.y - Mouse_Position.y)>150)
		{
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
		UI_Layer->setPosition(Vec2(Hero_Position.x - 640, Hero_Position.y - 360));
		Camera::getDefaultCamera()->setPosition(Hero_Position);
	}

	this->scheduleOnce(schedule_selector(InGame_Chapter_2_2::FireCheck), hero->FireDelay);
	static float time = 0;
	time += delta;
	static bool flametime = true;
	static float timecheak = time;
	static unsigned int Flame;
	static bool FlameOnce = true;
	if (flametime == true)
	{
		if (Monster->FindTarget && FlameOnce)
		{
			Flame = SimpleAudioEngine::sharedEngine()->playEffect("Sound/gun sound/FlameThrower.wav");
			FlameOnce = false;
		}
		this->scheduleOnce(schedule_selector(InGame_Chapter_2_2::MonsterFireCheck), 0.02f);
		if (time - timecheak >= 5.0f)
		{
			SimpleAudioEngine::sharedEngine()->stopEffect(Flame);
			timecheak = time;
			flametime = false;
		}
	}
	else if (time - timecheak >= 3.0f)
	{
		FlameOnce = true;
		timecheak = time;
		flametime = true;
	}

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

	switch (Singleton::GetInstance()->ClearMode)
	{
	case 0:
		Director::getInstance()->replaceScene(InGame_Chapter_2_2::createScene());
		break;
	case 1:
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/MainMenu (Party Hard).wav", true);
		Director::getInstance()->replaceScene(ChapterSelect::createScene());
		break;
	default:
		break;
	}

	MonsterCrash();
	HeroCrash();


	if (F->CollisionCheak(Point(0, 0), std::string("Exit"), hero->HeroImage, TileMap)
		&& Monster->Monster==nullptr)
	{
		if (Once)
		{
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
	if (Skill_4 != true)
	hero->HeroChange(Singleton::GetInstance()->WeaponCode, hero->AkimboCheak);
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
}

void InGame_Chapter_2_2::Door_Move()
{
	std::string open = "open"; //첫번째문
	bool cheak = F->CollisionCheak(Point(0, 0), open, hero->HeroImage, TileMap);
	auto Door_Move1 = MoveBy::create(0.3f, Vec2(100, 0));
	auto Door_Move2 = MoveBy::create(0.3f, Vec2(-100, 0));
	if (cheak == true && OpenCheak1 == false)
	{
		Door[0]->runAction(Door_Move1);
		Door[1]->runAction(Door_Move2);
		OpenCheak1 = true;
	}
	else if (cheak == false && OpenCheak1 == true)
	{
		Door[0]->runAction(Door_Move1->reverse());
		Door[1]->runAction(Door_Move2->reverse());
		OpenCheak1 = false;
	}
}

void InGame_Chapter_2_2::menuCallback(Ref * pSender)
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
		break;

	case 4:
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/MainMenu (Party Hard).wav", true);
		Director::getInstance()->replaceScene(ChapterSelect::createScene());
		break;
	default:
		break;
	}
}

void InGame_Chapter_2_2::goCall()
{
	hero->Invincibility = false;
	hero->HeroImage->runAction(Show::create());
}

void InGame_Chapter_2_2::FireCheck(float delta)
{
	if (hero->ShotCheck&&Skill_4!=true)
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

void InGame_Chapter_2_2::MonsterFireCheck(float delta)
{
	if (Monster->Monster != nullptr)
	{
		if (Monster->MonsterShotCheck&&hero->Hero_HP > 0)
		{
			Monster->MonsterbulletPositon->bulletPosition(Monster->MonsterWeaponCode, Monster->Monster, 0, false, false);
			Monster->MonsterContainerCheck = true;
		}
	}
}

void InGame_Chapter_2_2::RadarMonsterCheak()
{
	static int delay = 0;

	Vec2 Pos;
	bool fire = false;
	if (F->CollisionCheak(Vec2::ZERO, "Radar", hero->HeroImage, TileMap))
	{
		Monster->LookTarget(hero->HeroImage, true, TileMap);
	}
}


void InGame_Chapter_2_2::MonsterCrash()
{
	if (Monster->MonsterContainerCheck)
	{
		for (Sprite * v : Monster->MonsterbulletPositon->MonsterbulletContainer)
		{
			if (F->CrashRect(v, hero->HeroImage))
			{
				if (hero->Invincibility == false)
				{
					if (hero->Hero_HP > 0)
					{
						if (hero->NoDead != true)
						{
							hero->HeroImage->runAction(Sequence::create(Blink::create(2.5f, 9), CallFunc::create(CC_CALLBACK_0(InGame_Chapter_2_2::goCall, this)), NULL));
							hero->Hero_HP--;
						}
					}
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
						Monster->Space->pause();
						Once2 = false;
					}
				}
				hero->Invincibility = true;
				v->setTag(1);
			}
		}

		for (auto check = Monster->MonsterbulletPositon->MonsterbulletContainer.begin(); check != Monster->MonsterbulletPositon->MonsterbulletContainer.end();)
		{
			Sprite * v = (*check);
			bool Cheak = F->CollisionCheak(Vec2::ZERO, std::string("BulletCollision"), v, TileMap);
			if (v->getTag()==1
				|| F->CrashRect(v, Door[0])
				|| F->CrashRect(v, Door[1])
				|| F->CrashRect(v, elevatordoor[0])
				|| F->CrashRect(v, elevatordoor[1])
				|| Cheak)
			{
				v->removeFromParent();
				check = Monster->MonsterbulletPositon->MonsterbulletContainer.erase(check);
			}
			else
				++check;
		}
	}
}

void InGame_Chapter_2_2::HeroCrash()
{
	if (hero->HeroContainerCheck)
	{
		for (Sprite * v : hero->bulletposition->bulletContainer)
		{
			if (v != nullptr)
				if (v->getTag() == 6)
					hero->bulletposition->AfterEffect(v);
		}

		for (Sprite *v : hero->bulletposition->bulletContainer)
		{
			if (Monster->Monster != nullptr)
			{
				if (F->CrashRect(v, Monster->Monster))
				{
					if (Monster->Monster_Boss_2_2 > 0)
					{
						Monster->Monster_Boss_2_2 -= hero->bulletposition->Bullet_Damage;
						Monster->bar->SetPercentage(Monster->Monster_Boss_2_2 / 20);
					}
					if (Monster->Monster_Boss_2_2 <= 0)
					{
						SimpleAudioEngine::sharedEngine()->stopAllEffects();
						Lock = false;
						char Death[50];
						sprintf(Death, "Sound/enemy_death/enemy_death_%d.wav", RandomHelper::random_int(0, 2));
						SimpleAudioEngine::getInstance()->playEffect(Death);
						elevatordoor[0]->runAction(MoveBy::create(0.3f, Vec2(-100, 0)));
						elevatordoor[1]->runAction(MoveBy::create(0.3f, Vec2(100, 0)));
						Monster->bar->Remove();
						weapon = Weapon::createandinit(Monster->MonsterWeaponCode);
						MonsterWeapon = weapon;
						MonsterWeapon->setPosition(Monster->Monster->getPosition());
						MonsterWeapon->setTag(Monster->MonsterWeaponCode);

						this->addChild(MonsterWeapon);

						Monster->Monster->setTexture("Monster/PowerfulEnemy/Powerful_Death.png");
						Monster->Monster->setScale(1.15f);
						Monster->Monster->setFlippedY(true);
						Monster->Space->removeFromParent();
						float * vpos = F->DirPos(v->getRotation());
						Monster->Monster->runAction(Sequence::create(MoveBy::create(0.2f, Vec2(vpos[0] * 30, vpos[1] * 30)), DelayTime::create(3.0f), RemoveSelf::create(), NULL));
						Monster->Monster = nullptr;
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
		for (auto check = hero->bulletposition->bulletContainer.begin(); check != hero->bulletposition->bulletContainer.end();)
		{
			Sprite * v = (*check);
			Vec2 vpos = v->getPosition();
			bool Cheak = F->CollisionCheak(Point(0, 0), std::string("BulletCollision"), v, TileMap);
			if (v->getTag() == 1
				|| F->CrashRect(v, Door[0])
				|| F->CrashRect(v, Door[1])
				|| F->CrashRect(v, elevatordoor[0])
				|| F->CrashRect(v, elevatordoor[1])
				|| Cheak
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
					check = hero->bulletposition->bulletContainer.erase(check);
				}
				else
				{
					v->removeFromParent();
					check = hero->bulletposition->bulletContainer.erase(check);
				}
			}
			else
				++check;
		}
	}

	if (MonsterWeapon != nullptr)
	{
		if (F->CrashRect(hero->HeroImage, MonsterWeapon))
		{
			if (Key_F)
			{
				hero->AkimboCheak = false;
				Singleton::GetInstance()->WeaponCode = MonsterWeapon->getTag();

				ui->update(Singleton::GetInstance()->WeaponCode);

				MonsterWeapon->removeFromParent();
				MonsterWeapon = nullptr;
			}
			ui->HandImage->setVisible(true);
		}
		else
			ui->HandImage->setVisible(false);
	}
	else
		ui->HandImage->setVisible(false);
}

Vec2 InGame_Chapter_2_2::MonsterObjLayerPos(char * LayerName)
{
	MonsterPoint = objectGroup->getObject(LayerName);
	Vec2 Pos = Point(MonsterPoint["x"].asInt(), MonsterPoint["y"].asInt());
	return Pos;
}