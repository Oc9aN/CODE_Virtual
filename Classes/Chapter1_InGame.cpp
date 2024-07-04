#include "Chapter1_InGame.h"

Singleton* Singleton::getInstance = nullptr;

void InGame_Chapter_1::AkimboRemove(float dt)
{
	hero->AkimboCheak = false;
}

void InGame_Chapter_1::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
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
		Director::getInstance()->replaceScene(InGame_Chapter_1::createScene());
		break;
	case EventKeyboard::KeyCode::KEY_F8:
		hero->NoDead = true;
		hero->Shield();
		break;
	case EventKeyboard::KeyCode::KEY_F9:
		hero->NoDead = false;
		break;
	case EventKeyboard::KeyCode::KEY_1:
			hero->AkimboCheak = true;
			this->scheduleOnce(schedule_selector(InGame_Chapter_1::AkimboRemove),5.0f);
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
			hero->Space->setPosition(Vec2(hero->HeroImage->getContentSize().width / 2 + 10,
				hero->HeroImage->getContentSize().height / 2 - 8));
			hero->HeroImage->setTexture("Skill/BladeDancer_0.png");
			this->scheduleOnce(schedule_selector(InGame_Chapter_2::Skill_4_Remove), 8.0f);
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

void InGame_Chapter_1::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
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

bool InGame_Chapter_1::onTouchBegan(Touch * touch, Event * event)
{
	if (Skill_4)
	{
		auto Blade = Animation::create();
		for (int i = 0; i < 3; i++)
		{
			char str[100] = { 0 };
			sprintf(str, "Skill/BladeDancer_%d.png", i);
			Blade->addSpriteFrameWithFile(str);
		}
		Blade->setDelayPerUnit(0.1f);
		auto BladeDancerM = Animate::create(Blade);
		BladeDancerRep = RepeatForever::create(BladeDancerM);
		hero->HeroImage->runAction(BladeDancerRep);
	}
	if (Singleton::GetInstance()->WeaponCode == 4)
		FlameSound = SimpleAudioEngine::sharedEngine()->playEffect("Sound/gun sound/FlameThrower.wav");
	hero->ShotCheck = true;
	return true;
}

void InGame_Chapter_1::onTouchEnded(Touch * touch, Event * event)
{
	if (Skill_4)
	{
		hero->HeroImage->stopAction(BladeDancerRep);
		hero->HeroImage->setTexture("Skill/BladeDancer_0.png");
	}
	if (Singleton::GetInstance()->WeaponCode == 4)
		SimpleAudioEngine::sharedEngine()->stopEffect(FlameSound);
	hero->ShotCheck = false;

}

void InGame_Chapter_1::onMouseMove(cocos2d::Event * event)
{
	auto mouseEvent = static_cast<EventMouse*>(event);
	Mouse_Position = mouseEvent->getLocation();

	MouseScale.x = mouseEvent->getCursorX() - 640.0f;
	MouseScale.y = mouseEvent->getCursorY() - 360.0f;

	Hero_Angle = F->GetAngleOffset(mouseEvent->getLocation(), Vec2(640, 360), 1, 90);
	if (hero->Hero_HP > 0&&ui->Clear!=true&&SHIFT!=true)
		hero->HeroImage->setRotation(Hero_Angle);
}

Scene * InGame_Chapter_1::createScene()
{
	auto scene = Scene::create();

	auto layer = InGame_Chapter_1::create();

	scene->addChild(layer);

	return scene;
}

bool InGame_Chapter_1::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->setKeyboardEnabled(true);
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	TileMap = TMXTiledMap::create("Map/Map.tmx"); //맵 레이어
	this->addChild(TileMap);
	
	Once = true;
	Skill_4 = false;
	Once2 = true;
	Key_4 = true;
	Key_F = false;


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
	hero->bulletposition = new BulletPosition(BulletLayer);
	hero->HeroImage->setPosition(Vec2(300, 300));
	ui = new UI(UI_Layer);
	this->addChild(UI_Layer, 99);

	PauseLayer = Layer::create();
	PauseLayer->setPosition(Vec2(-10000, -10000));
	this->addChild(PauseLayer,UI_Layer->getZOrder()+1);

	auto Mouse = EventListenerMouse::create();
	Mouse->onMouseMove = CC_CALLBACK_1(InGame_Chapter_1::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Mouse, this);


	auto Pausebackground_Light = Sprite::create("UI/Pause_Background_Light.png");
	Pausebackground_Light->setPosition(Vec2(640, 360));
	PauseLayer->addChild(Pausebackground_Light);

	auto Pausebackground = Sprite::create("UI/Pause_Background.png");
	Pausebackground->setPosition(Vec2(640, 360));
	PauseLayer->addChild(Pausebackground);

	auto Resume = MenuItemImage::create("UI/Pause_resume_off.png", "UI/Pause_resume_on.png", "UI/Pause_resume_on.png", CC_CALLBACK_1(InGame_Chapter_1::menuCallback, this));
	Resume->setTag(2);
	auto Option = MenuItemImage::create("UI/Pause_option_off.png", "UI/Pause_option_on.png", "UI/Pause_option_on.png", CC_CALLBACK_1(InGame_Chapter_1::menuCallback, this));
	Option->setTag(3);
	auto P_Menu = MenuItemImage::create("UI/Pause_menu_off.png", "UI/Pause_menu_on.png", "UI/Pause_menu_on.png", CC_CALLBACK_1(InGame_Chapter_1::menuCallback, this));
	P_Menu->setTag(4);

	auto Pause_Menu = Menu::create(Resume, Option, P_Menu, NULL);
	Pause_Menu->setPosition(Vec2(640, 225));
	Pause_Menu->alignItemsVertically();
	Pause_Menu->alignItemsVerticallyWithPadding(50.f);
	PauseLayer->addChild(Pause_Menu);

	Option_Layer = Layer::create();
	Option_Layer->setPosition(Point(-10000,-10000));

	ui->Option(Option_Layer);

	auto Back = MenuItemImage::create("UI/Back_off.png", "UI/Back_on.png", "UI/Back_on.png", CC_CALLBACK_1(InGame_Chapter_1::menuCallback, this));
	Back->setTag(5);
	auto Menu_Back = Menu::create(Back, NULL);
	Menu_Back->setPosition(Vec2(1000, 550));
	Option_Layer->addChild(Menu_Back);
	this->addChild(Option_Layer,PauseLayer->getZOrder()+1);

	char MonsterName[15];
	objectGroup = TileMap->objectGroupNamed("Monster"); //몬스터 위치 오브젝트

	for (int i = 0; i < 8; i++)
	{
		Monster[i] = new C_Monster(MonsterLayer);
		Monster[i]->MonsterbulletPositon = new BulletPosition(BulletLayer);
		sprintf(MonsterName, "Monster_%d", i + 1);
		MonsterPoint = objectGroup->getObject(MonsterName);
		int Monster_x = MonsterPoint["x"].asInt();
		int Monster_y = MonsterPoint["y"].asInt();
		Monster[i]->Monster->setPosition(Monster_x, Monster_y);
	}

	for (int x = 0; x < 4; x++)
	{
		if (x < 2)
			Door[x] = Sprite::create(StringUtils::format("Map/Map/Door_%d.png", x % 2));
		else
		{
			Door[x] = Sprite::createWithSpriteFrame(Door[x - 2]->getSpriteFrame());
			Door[x]->setRotation(90.0f);
		}
		Door[x]->setAnchorPoint(Vec2(0, 0));
		switch (x)
		{
		case 0:
			Door[x]->setPosition(Vec2(600, 400));
			break;
		case 1:
			Door[x]->setPosition(Vec2(600, 200));
			break;
		case 2:
			Door[x]->setPosition(Vec2(1275, 1000));
			break;
		case 3:
			Door[x]->setPosition(Vec2(1075, 1000));
			break;
		}
		this->addChild(Door[x]);
	}

	OpenCheak1 = false; //첫번째문

	OpenCheak2 = false; //두번째문




	return true;
}

void InGame_Chapter_1::update(float delta)
{
	if (Singleton::GetInstance()->WeaponCode != 4)
		SimpleAudioEngine::sharedEngine()->stopEffect(FlameSound);
	for (int i = 0; i < 8; i++)
	{
		if (Monster[i]->Monster != nullptr && Skill_4 != true)
		{
			Monster[i]->bar->SetPosition(Vec2(Monster[i]->Monster->getPosition().x - 50, Monster[i]->Monster->getPosition().y - 217));
			if (Monster[i]->Arrive == true && i>4)
				Monster[i]->Monster_Move(TileMap);
	
			if (Monster[i]->Arrive)
				Monster[i]->Space->pause();
			else
				Monster[i]->Space->resume();
		}
	}
	Door_Move();
	RadarMonsterCheak();
	ui->Hero_Update(hero->Hero_HP);
	Hero_Position = hero->HeroImage->getPosition();

	bool Check_UP = F->CollisionCheak(Vec2(0, 25), std::string("collisionCheak"), hero->HeroImage, TileMap);
	bool Check_DONW = F->CollisionCheak(Vec2(0, -25), std::string("collisionCheak"), hero->HeroImage, TileMap);
	bool Check_LEFT = F->CollisionCheak(Vec2(-25, 0), std::string("collisionCheak"), hero->HeroImage, TileMap);
	bool Check_RIGHT = F->CollisionCheak(Vec2(25, 0), std::string("collisionCheak"), hero->HeroImage, TileMap);

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
		if (UP && Check_UP != true && SHIFT!=true)
			Hero_Position.y += 8;
		if (LEFT && Check_LEFT != true && SHIFT != true)
			Hero_Position.x -= 8;
		if (DOWN && Check_DONW != true && SHIFT != true)
			Hero_Position.y -= 8;
		if (RIGHT && Check_RIGHT != true && SHIFT != true)
			Hero_Position.x += 8;
	}
	hero->HeroImage->setPosition(Hero_Position);

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

	this->scheduleOnce(schedule_selector(InGame_Chapter_1::FireCheck), hero->FireDelay);
	this->scheduleOnce(schedule_selector(InGame_Chapter_1::MonsterFireCheck), 0.8f);

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
		Director::getInstance()->replaceScene(InGame_Chapter_1::createScene());
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

	if (F->CollisionCheak(Vec2(0, 0), std::string("Exit"), hero->HeroImage, TileMap)
		&& Monster[0]->Monster == nullptr
		&&Monster[1]->Monster == nullptr
		&&Monster[2]->Monster == nullptr
		&&Monster[3]->Monster == nullptr
		&&Monster[4]->Monster == nullptr
		&&Monster[5]->Monster == nullptr
		&&Monster[6]->Monster == nullptr
		&&Monster[7]->Monster == nullptr)
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
	if(Skill_4!=true)
	hero->HeroChange(Singleton::GetInstance()->WeaponCode, hero->AkimboCheak);

	if (ui->Magazine_Num == 0)
	{
		Singleton::GetInstance()->WeaponCode = -1;
		ui->Magazine_Label->setString("8");
		ui->Magazine_Label->setRotation(90.0f);
		ui->Magazine_Label->setScale(1.3f);
		ui->Magazine_Label->setPosition(Vec2(78,605));
	}
	else
	{
		ui->Magazine_Label->setRotation(0.0f);
		ui->Magazine_Label->setScale(1.0f);
		ui->Magazine_Label->setPosition(Vec2(70, 605));
	}
}

void InGame_Chapter_1::Door_Move()
{
	std::string open = "open"; //첫번째문
	bool cheak = F->CollisionCheak(Vec2(0, 0), open, hero->HeroImage, TileMap);
	auto Door_Move1 = MoveBy::create(0.3f, Vec2(0, 100));
	auto Door_Move2 = MoveBy::create(0.3f, Vec2(0, -100));
	auto Door_Move3 = MoveBy::create(0.3f, Vec2(125, 0));
	auto Door_Move4 = MoveBy::create(0.3f, Vec2(-125, 0));
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
	cheak = F->CollisionCheak(Vec2(0, 0), open, hero->HeroImage, TileMap);
	if (cheak == true && OpenCheak2 == false)
	{
		Door[2]->runAction(Door_Move3);
		Door[3]->runAction(Door_Move4);
		OpenCheak2 = true;
	}
	else if (cheak == false && OpenCheak2 == true)
	{
		Door[2]->runAction(Door_Move3->reverse());
		Door[3]->runAction(Door_Move4->reverse());
		OpenCheak2 = false;
	}
}
void InGame_Chapter_1::menuCallback(Ref * pSender)
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
		Option_Layer->setPosition(Point(-10000,-10000));
		break;
	default:
		break;
	}
}
void InGame_Chapter_1::FireCheck(float delta)
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
			ui->Magazine_Label->setString(StringUtils::format("%d",ui->Magazine_Num));

		}
		hero->HeroContainerCheck = true;
	}

}

void InGame_Chapter_1::MonsterFireCheck(float delta)
{
	for (int i = 0; i < 8; i++)
	{
		if (Monster[i]->Monster != nullptr)
		{
			if (Monster[i]->MonsterShotCheck&&hero->Hero_HP>0)
			{
				Monster[i]->MonsterbulletPositon->bulletPosition(Monster[i]->MonsterWeaponCode, Monster[i]->Monster, 0, false, false);
				Monster[i]->MonsterContainerCheck = true;
			}
		}
	}
}


void InGame_Chapter_1::RadarMonsterCheak()
{
	static int delay = 0;

	Vec2 Pos;
	bool fire = false;
	char LayerName[10];
	for (int i = 1; i < 6; i++)
	{
		sprintf(LayerName, "Radar_%d", i);
		std::string Str = LayerName;
		bool cheak = F->CollisionCheak(Vec2(0, 0), Str, hero->HeroImage, TileMap);
		if (cheak == true)
		{
			if (i == 1) //1번레이더는 몬스터가 안움직임
			{
				std::fill_n(Fallow, 3, true);
				Monster[0]->LookTarget(hero->HeroImage, false, TileMap);
				Monster[1]->LookTarget(hero->HeroImage, false, TileMap);
			}
			else if (i == 2) //3번몬스터,6번몬스터 움직임
			{
				Monster[4]->MonsterShotCheck = false;
				Monster[0]->MonsterShotCheck = false;
				Monster[1]->MonsterShotCheck = false;
				Fallow[0] = true;
				Fallow[1] = false;
				Monster[2]->LookTarget(hero->HeroImage, true, TileMap);
				Monster[5]->LookTarget(hero->HeroImage, true, TileMap);
			}
			else if (i == 3) //4번몬스터,7번몬스터 움직임
			{
				Monster[4]->MonsterShotCheck = false;
				Fallow[0] = false;
				Fallow[1] = true;
				Fallow[2] = true;
				Monster[3]->LookTarget(hero->HeroImage, true, TileMap);
				Monster[6]->LookTarget(hero->HeroImage, true, TileMap);
			}
			else if (i == 4) //8번몬스터움직임
			{
				Monster[4]->MonsterShotCheck = false;
				Fallow[0] = true;
				Fallow[1] = false;
				Fallow[2] = false;
				Monster[7]->LookTarget(hero->HeroImage, true, TileMap);
			}
			else if (i == 5) //5번몬스터는 안움직임
			{
				Monster[0]->MonsterShotCheck = false;
				Monster[1]->MonsterShotCheck = false;
				Fallow[0] = true;
				Fallow[1] = false;
				Fallow[2] = true;
				if (hero->HeroImage->getPosition().y >= 1000)
					Monster[4]->LookTarget(hero->HeroImage, false, TileMap);
			}
		}
	}

	if (Fallow[0] == true && (Monster[3]->Arrive == false || Monster[6]->Arrive == false)) //4번몬스터,7번몬스터 돌아옴
	{
		if (Monster[3]->Monster != nullptr)
		{
			Pos = MonsterObjLayerPos("Monster_4"); //몬스터4번 좌표가져오기
			Monster[3]->retrunPos(Pos, TileMap);
		}

		if (Monster[6]->Monster != nullptr)
		{
			Pos = F->FindWay(Monster[6]->Monster,TileMap); //몬스터7번 가장가까운길 좌표가져오기
			Monster[6]->retrunPos(Pos, TileMap);
		}
	}
	if (Fallow[1] == true && (Monster[2]->Arrive == false || Monster[5]->Arrive == false)) //3번몬스터,6번몬스터 돌아옴
	{
		if (Monster[2]->Monster != nullptr)
		{
			Pos = MonsterObjLayerPos("Monster_3"); //몬스터3번 좌표가져오기
			Monster[2]->retrunPos(Pos, TileMap);
		}

		if (Monster[5]->Monster != nullptr)
		{
			Pos = F->FindWay(Monster[5]->Monster,TileMap); //몬스터6번 가장가까운길 좌표가져오기
			Monster[5]->retrunPos(Pos, TileMap);
		}
	}
	if (Fallow[2] == true && Monster[7]->Arrive == false) //8번몬스터
	{
		if (Monster[7]->Monster != nullptr)
		{
			Pos = F->FindWay(Monster[7]->Monster,TileMap); //몬스터8번 가장가까운길 좌표가져오기
			Monster[7]->retrunPos(Pos, TileMap);
		}
	}
}


Vec2 InGame_Chapter_1::MonsterObjLayerPos(char * LayerName)
{
	MonsterPoint = objectGroup->getObject(LayerName);
	Vec2 Pos = Vec2(MonsterPoint["x"].asInt(), MonsterPoint["y"].asInt());
	return Pos;
}

void InGame_Chapter_1::MonsterCrash()
{
	for (int x = 0; x < 8; x++)
	{
		if (Monster[x]->MonsterContainerCheck)
		{
			for (Sprite *v : Monster[x]->MonsterbulletPositon->MonsterbulletContainer)
			{
				if (F->CrashRect(v, hero->HeroImage))
				{
					if (hero->Invincibility == false)
					{
						if (hero->Hero_HP > 0)
						{
							if (hero->NoDead != true)
							{
								hero->HeroImage->runAction(Sequence::create(Blink::create(2.5f, 9), CallFunc::create(CC_CALLBACK_0(InGame_Chapter_1::goCall, this)), NULL));
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
							Once2 = false;
						}
					}
					hero->Invincibility = true;
					v->setTag(1);
				}

			}
			for (auto check = Monster[x]->MonsterbulletPositon->MonsterbulletContainer.begin(); check != Monster[x]->MonsterbulletPositon->MonsterbulletContainer.end();)
			{
				Sprite * v = (*check);
				bool Cheak = F->CollisionCheak(Vec2(0, 0), std::string("BulletCollision"), v, TileMap);
				if (v->getTag()==1
					|| F->CrashRect(v, Door[0])
					|| F->CrashRect(v, Door[1])
					|| F->CrashRect(v, Door[2])
					|| F->CrashRect(v, Door[3])
					|| Cheak)
				{
					v->removeFromParent();
					check = Monster[x]->MonsterbulletPositon->MonsterbulletContainer.erase(check);
				}
				else
					++check;
			}
		}
	}
}

void InGame_Chapter_1::Skill_4_Remove(float delta)
{
	Key_4 = true;
	Skill_4 = false;
	hero->Space->setPosition(Vec2(hero->HeroImage->getContentSize().width / 2-25, hero->HeroImage->getContentSize().height / 2 - 8));
	hero->HeroImage->stopAllActions();
	hero->HeroImage->setVisible(true);
}

void InGame_Chapter_1::HeroCrash()
{
	if (Skill_4 && hero->ShotCheck)
	{
		for (int x = 0; x < 8; x++)
		{
			if (Monster[x]->Monster != nullptr)
			{
				if (F->CrashRect(hero->HeroImage, Monster[x]->Monster))
				{
					Monster[x]->bar->Remove();
					weapon = Weapon::createandinit(Monster[x]->MonsterWeaponCode);
					MonsterWeapon[x] = weapon;
					MonsterWeapon[x]->setPosition(Monster[x]->Monster->getPosition());
					MonsterWeapon[x]->setTag(Monster[x]->MonsterWeaponCode);
					this->addChild(MonsterWeapon[x]);

					int a = (Monster[x]->FindTarget) ? 0 : 1;
					Monster[x]->Monster->setTexture(StringUtils::format("Monster/Monster_Dead_%d.png", a));
					Monster[x]->Monster->setScale(1.4f);
					Monster[x]->Space->removeFromParent();

					if (a == 0)
					{
						Monster[x]->Monster->setFlippedY(true);
						Monster[x]->Monster->setRotation(Hero_Angle - 180.0f);
					}
					if (a == 1)
					{
						if (Monster[x]->Monster->getRotation() == 180.0f || Monster[x]->Monster->getRotation() == 90.0f)
							Monster[x]->Monster->setTexture("Monster/Monster_Dead_0.png");

						Monster[x]->Monster->setRotation(Hero_Angle);
					}
					Monster[x]->Monster->runAction(Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(), NULL));
					Monster[x]->Monster = nullptr;
				}
			}
		}
	}

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
			for (int x = 0; x < 8; x++)
			{
				if (Monster[x]->Monster != nullptr)
				{
					if (F->CrashRect(v, Monster[x]->Monster))
					{
						Monster[x]->Monster_HP -= hero->bulletposition->Bullet_Damage;
						Monster[x]->bar->SetPercentage(Monster[x]->Monster_HP / 3);
						if (Monster[x]->Monster_HP <= 0)
						{
							char Death[50];
							sprintf(Death, "Sound/enemy_death/enemy_death_%d.wav", RandomHelper::random_int(0, 2));
							SimpleAudioEngine::getInstance()->playEffect(Death);
							Monster[x]->bar->Remove();
							weapon = Weapon::createandinit(Monster[x]->MonsterWeaponCode);
							MonsterWeapon[x] = weapon;
							MonsterWeapon[x]->setPosition(Monster[x]->Monster->getPosition());
							MonsterWeapon[x]->setTag(Monster[x]->MonsterWeaponCode);

							this->addChild(MonsterWeapon[x]);

							int a = (Monster[x]->FindTarget) ? 0 : 1;
							Monster[x]->Monster->setTexture(StringUtils::format("Monster/Monster_Dead_%d.png", a));
							Monster[x]->Monster->setScale(1.4f);
							Monster[x]->Space->removeFromParent();

							if (a == 0)
							{
								Monster[x]->Monster->setFlippedY(true);
								Monster[x]->Monster->setRotation(Hero_Angle - 180.0f);
							}
							if (a == 1)
							{
								if (Monster[x]->Monster->getRotation() == 180.0f || Monster[x]->Monster->getRotation() == 90.0f)
									Monster[x]->Monster->setTexture("Monster/Monster_Dead_0.png");

								Monster[x]->Monster->setRotation(Hero_Angle);
							}

							float * vpos = F->DirPos(v->getRotation());
							Monster[x]->Monster->runAction(Sequence::create(MoveBy::create(0.2f, Vec2(vpos[0] * 30, vpos[1] * 30)), DelayTime::create(3.0f), RemoveSelf::create(), NULL));
							Monster[x]->Monster = nullptr;
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
		}

		for (auto check = hero->bulletposition->bulletContainer.begin(); check != hero->bulletposition->bulletContainer.end();)
		{
			Sprite * v = (*check);
			Vec2 vpos = v->getPosition();
			bool Cheak = F->CollisionCheak(Vec2(0, 0), std::string("BulletCollision"), v, TileMap);
			if (v->getTag() == 1
				|| F->CrashRect(v, Door[0])
				|| F->CrashRect(v, Door[1])
				|| F->CrashRect(v, Door[2])
				|| F->CrashRect(v, Door[3])
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
			{
				++check;
			}
		}
	}

	for (int x = 0; x < 8; x++)
	{
		if (MonsterWeapon[x] != nullptr)
		{
			if (F->CrashRect(hero->HeroImage, MonsterWeapon[x]))
			{
				if (Key_F)
				{
					hero->AkimboCheak = false;
					Singleton::GetInstance()->WeaponCode = MonsterWeapon[x]->getTag();

					ui->update(Singleton::GetInstance()->WeaponCode);

					MonsterWeapon[x]->removeFromParent();
					MonsterWeapon[x] = nullptr;
				}
				ui->HandImage->setVisible(true);
				break;
			}
			else
				ui->HandImage->setVisible(false);
		}
		else
			ui->HandImage->setVisible(false);
	}

}

void InGame_Chapter_1::goCall()
{
	hero->Invincibility = false;
	hero->HeroImage->runAction(Show::create());
}
