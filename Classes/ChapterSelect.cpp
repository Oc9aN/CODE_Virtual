#include "ChapterSelect.h"

Scene * ChapterSelect::createScene()
{
	auto scene = Scene::create();
	auto layer = ChapterSelect::create();
	scene->addChild(layer);
	return scene;
}

bool ChapterSelect::init()
{
	
	if (!Layer::init())
	{
		return false;
	}
	Director::getInstance()->resume();
	SightOff = Vec2(-10000, -10000);
	MainCenter = Vec2(640, 360);

	for (int x = 0; x < 2; x++)
	{
		Chapter_Layer[x] = Layer::create();
		Chapter_Layer[x]->setPosition(SightOff);
		this->addChild(Chapter_Layer[x], 2);
	}

	Option_Layer = Layer::create();
	Option_Layer->setPosition(SightOff);

	ui->Option(Option_Layer);

	Chapter_Backgrond = Sprite::create("UI/Chapter_Background_00.png");
	Chapter_Backgrond->setPosition(MainCenter);
	this->addChild(Chapter_Backgrond);

	auto Chapter_Name = Sprite::create("UI/Chapter_Name.png");
	Chapter_Name->setPosition(Vec2(Chapter_Backgrond->getContentSize().width/2, Chapter_Backgrond->getContentSize().height/2));
	Chapter_Backgrond->addChild(Chapter_Name);

	auto Option = MenuItemImage::create("UI/Option_off.png", "UI/Option_on.png", "UI/Option_on.png", CC_CALLBACK_1(ChapterSelect::menuCallback, this));
	Option->setTag(3);
	OptionMenu = Menu::create(Option, NULL);
	OptionMenu->setPosition(Vec2(1185, 627));
	this->addChild(OptionMenu);

	auto Back = MenuItemImage::create("UI/Back_off.png", "UI/Back_on.png", "UI/Back_on.png", CC_CALLBACK_1(ChapterSelect::menuCallback, this));
	Back->setTag(4);
	auto Menu_Back = Menu::create(Back, NULL);
	Menu_Back->setPosition(Vec2(1000, 550));
	Option_Layer->addChild(Menu_Back);

	this->addChild(Option_Layer, 2);

	Chapter_1 = MenuItemImage::create("UI/chapter_0_on.png", "UI/chapter_0_off.png", "UI/chapter_0_off.png", CC_CALLBACK_1(ChapterSelect::menuCallback, this));
	Chapter_1->setTag(1);
	Chapter_2 = MenuItemImage::create("UI/chapter_1_on.png", "UI/chapter_1_off.png", "UI/chapter_1_off.png", CC_CALLBACK_1(ChapterSelect::menuCallback, this));
	Chapter_2->setTag(2);
	Chapter_1->setEnabled(false);
	Chapter_2->setEnabled(true);
	menu = Menu::create(Chapter_1, Chapter_2, NULL);
	menu->setPosition(Vec2(0, 435));
	menu->runAction(MoveBy::create(0.25f, Vec2(120, 0)));
	menu->alignItemsVertically();
	menu->alignItemsVerticallyWithPadding(25.0f);
	this->addChild(menu);

	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			Chapter_Number[x][y] = MenuItemImage::create("UI/ChapterTouch_off.png", "UI/ChapterTouch_on.png", "UI/ChapterTouch_on.png", CC_CALLBACK_1(ChapterSelect::menuCallback, this));
			Chapter_Number[x][y]->setPosition(Vec2(555 + (500 * y), 440 - (280 * x)));
		
			WhiteSide[x][y] = Sprite::create("UI/WhiteSide.png");
			WhiteSide[x][y]->setPosition(Vec2(Chapter_Number[x][y]->getContentSize().width/2,Chapter_Number[x][y]->getContentSize().height/2));
			WhiteSide[x][y]->setVisible(false);
			Chapter_Number[x][y]->addChild(WhiteSide[x][y], -1);
			
			Chapter_Number2[x][y] = MenuItemImage::create("UI/ChapterTouch_off.png", "UI/ChapterTouch_on.png", "UI/ChapterTouch_on.png", CC_CALLBACK_1(ChapterSelect::menuCallback, this));
			Chapter_Number2[x][y]->setPosition(Vec2(555 + (500 * y), 440 - (280 * x)));
			Chapter_Number2[x][y]->setRotation(90.0f);

			Number[x][y] = Sprite::create(StringUtils::format("UI/Number_%d_%d.png", x, y));
			Number[x][y]->setPosition(Vec2(Chapter_Number[x][y]->getContentSize().width/2, Chapter_Number[x][y]->getContentSize().height/2));
			Chapter_Number[x][y]->addChild(Number[x][y]);

			Number[x][y] = Sprite::create(StringUtils::format("UI/Number_%d_%d.png", x, y));
			Number[x][y]->setPosition(Vec2(Chapter_Number2[x][y]->getContentSize().width / 2, Chapter_Number2[x][y]->getContentSize().height / 2));
			Number[x][y]->setRotation(-90.0f);
			Chapter_Number2[x][y]->addChild(Number[x][y]);
		}
	}

	auto Mouse = EventListenerMouse::create();
	Mouse->onMouseMove = CC_CALLBACK_1(ChapterSelect::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Mouse, this);

	Chapter_Number[0][0]->setTag(5);
	Chapter_Number[0][1]->setTag(6);
	Chapter_Number[1][0]->setTag(7);
	Chapter_Number[1][1]->setTag(8);
	Chapter_Number2[0][0]->setTag(9);
	Chapter_Number2[0][1]->setTag(10);
	Chapter_Number2[1][0]->setTag(11);
	Chapter_Number2[1][1]->setTag(12);

	ChapterMenu = Menu::create(Chapter_Number[0][0], Chapter_Number[0][1], Chapter_Number[1][0], Chapter_Number[1][1], NULL);
	ChapterMenu->setPosition(Vec2::ZERO);
	Chapter_Layer[0]->addChild(ChapterMenu);

	ChapterMenu2 = Menu::create(Chapter_Number2[0][0], Chapter_Number2[0][1], Chapter_Number2[1][0], Chapter_Number2[1][1], NULL);
	ChapterMenu2->setPosition(Vec2::ZERO);
	Chapter_Layer[1]->addChild(ChapterMenu2);

	this->scheduleOnce(schedule_selector(ChapterSelect::Chapteronce), 0.45f);

	return true;
}

void ChapterSelect::Chapteronce(float delta)
{
	Chapter_Layer[0]->setPosition(Vec2::ZERO);
}

void ChapterSelect::onMouseMove(cocos2d::Event * event)
{
	auto mouseEvent = static_cast<EventMouse*>(event);

	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			if (Chapter_Number[x][y]->getBoundingBox().containsPoint(Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY())))
			{
				WhiteSide[x][y]->setVisible(true);
				Chapter_Backgrond->setTexture(StringUtils::format("UI/Chapter_Background_%d%d.png",x,y));
				
				break;
			}
			else
				WhiteSide[x][y]->setVisible(false);
		}
	}
}


void ChapterSelect::menuCallback(cocos2d::Ref * pSender)
{
	auto pTempItem = (CCMenuItem*)pSender;
	int i = pTempItem->getTag();

	switch (i)
	{
	case 1:
	{
		Chapter_Layer[0]->setPosition(Vec2::ZERO);
		Chapter_Layer[1]->setPosition(SightOff);

		Chapter_1->setEnabled(false);
		Chapter_2->setEnabled(true);
		this->setTouchEnabled(true);
	}
	break;
	case 2:
	{
		Chapter_Layer[0]->setPosition(SightOff);
		Chapter_Layer[1]->setPosition(Vec2::ZERO);

		Chapter_1->setEnabled(true);
		Chapter_2->setEnabled(false);
		this->setTouchEnabled(true);
	}
	break;
	case 3:
	{
		Option_Layer->setPosition(Vec2::ZERO);
		Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(menu);
		Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(ChapterMenu);
		Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(ChapterMenu2);
		Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(OptionMenu);

	}
	break;
	case 4:
	{
		Option_Layer->setPosition(SightOff);
		Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(menu);
		Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(ChapterMenu);
		Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(ChapterMenu2);
		Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(OptionMenu);
	}
	break;
	case 5:
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/Stage1_1.wav", true);
		ui->Sound();
		Director::getInstance()->replaceScene(InGame_Chapter_1::createScene());
	}
	break;
	case 6:
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/Stage2.wav", true);
		ui->Sound();
		Director::getInstance()->replaceScene(InGame_Chapter_2::createScene());
	}
	break;
	case 7:
	{
		Director::getInstance()->replaceScene(InGame_Chapter_2_2::createScene());
	}
	break;
	case 8:
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/BossStage2.wav", true);
		ui->Sound();
		Director::getInstance()->replaceScene(InGame_Boss::createScene());
	}
		break;
	default:
		break;
	}
}
