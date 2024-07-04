#include "UI.h"

UI::UI(Layer * layer)
{
	bool Clear = false;

	Singleton::GetInstance()->ClearMode = -1;
	Magazine = Sprite::create("UI/Magazine_Animation_3.png");
	Magazine->setPosition(Vec2(132, 600));
	Magazine->setScale(0.7f);
	layer->addChild(Magazine);

	auto MagazineBackground = Sprite::create("UI/Magazine_Background.png");
	MagazineBackground->setPosition(Vec2(Magazine->getContentSize().width / 2, Magazine->getContentSize().height / 2));
	Magazine->addChild(MagazineBackground, -1);

	Magazine_Label = Label::createWithTTF("8", "UI/Fixedsys.ttf", 56);
	Magazine_Label->setPosition(Vec2(70, 605));
	layer->addChild(Magazine_Label);

	Magazine_Num = 0;

	for (int x = 0; x < 4; x++)
	{
		Skill_Image[x] = MenuItemImage::create(StringUtils::format("Skill/Skill_%d.png", x), StringUtils::format("Skill/Skill_%d.png", x), StringUtils::format("Skill/Skill_%d.png", x));
		Skill_Number[x] = Sprite::create(StringUtils::format("Skill/Skill_Number_%d.png", x+1));
		Skill_Number[x]->setPosition(Vec2(Skill_Image[x]->getContentSize().width-10, 17));
		Skill_Number[x]->setScale(0.95f);
		Skill_Image[x]->addChild(Skill_Number[x]);
	}//스킬 이미지 생성

	auto Skill_Menu = Menu::create(Skill_Image[0], Skill_Image[1], Skill_Image[2], Skill_Image[3], NULL);
	Skill_Menu->setPosition(Vec2(640, 100));
	Skill_Menu->alignItemsHorizontally();
	Skill_Menu->alignItemsHorizontallyWithPadding(110.0f);
	layer->addChild(Skill_Menu);

	HandImage = Sprite::create("UI/hand123.png");
	HandImage->setPosition(Vec2(640, 450));
	HandImage->setVisible(false);
	layer->addChild(HandImage);

	bar = new UIProgressBar(layer);
	bar->SetPosition(Vec2(120,605));
	bar->SetBackgroundSprite(Sprite::create("UI/Flamethrower_Background.png"));
	bar->SetForegroundSprite(Sprite::create("UI/Flamethrower_Bar.png"));

	ClearLayer = layer;

	Health_bar = Sprite::create("UI/Health_bar_3.png");
	Health_bar->setPosition(Vec2(125, 669.5));
	Health_bar->setScale(0.7f);
	layer->addChild(Health_bar);
}

void UI::Option(Layer * layer)
{
	auto MainCenter = Vec2(640, 360);
	auto Option_Light = Sprite::create("UI/Option_Background_Light.png");
	Option_Light->setPosition(MainCenter);
	layer->addChild(Option_Light);

	auto Option_Background = Sprite::create("UI/Option_Background.png");
	Option_Background->setPosition(MainCenter);
	layer->addChild(Option_Background);

	auto Credit = MenuItemImage::create("UI/Credit_off.png", "UI/Credit_on.png", "UI/Credit_on.png", CC_CALLBACK_1(UI::menuCallback, this));
	Credit->setTag(5);
	auto Menu_Credit = Menu::create(Credit, NULL);
	Menu_Credit->setPosition(Vec2(640, 233));
	layer->addChild(Menu_Credit);

	MenuItemImage* Pink_On[2];
	MenuItemImage* Pink_Off[2];
	MenuItemToggle* toggle[2];
	bool Cheak[2] = { Singleton::GetInstance()->BGM , Singleton::GetInstance()->SFX };
	for (int x = 0; x < 2; x++)
	{
		Pink_On[x] = MenuItemImage::create("UI/Option_on_pink.png", "UI/Option_on_pink.png");
		Pink_Off[x] = MenuItemImage::create("UI/Option_off_pink.png", "UI/Option_off_pink.png");
		if(Cheak[x] == true)
			toggle[x] = MenuItemToggle::createWithCallback(CC_CALLBACK_1(UI::menuCallback, this), Pink_On[x], Pink_Off[x], NULL);
		else if(Cheak[x] == false)
			toggle[x] = MenuItemToggle::createWithCallback(CC_CALLBACK_1(UI::menuCallback, this), Pink_Off[x], Pink_On[x], NULL);
		toggle[x]->setTag(x + 3);
	}
	auto PinkMenu = Menu::create(toggle[0], toggle[1], NULL);
	PinkMenu->setPosition(Vec2(715, 407));
	PinkMenu->alignItemsHorizontally();
	PinkMenu->alignItemsHorizontallyWithPadding(225.0f);
	layer->addChild(PinkMenu, 2);
}

void UI::Sound()
{
	if (Singleton::GetInstance()->BGM)
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	else 
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

	if (Singleton::GetInstance()->SFX)
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0);
	else
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0);
}


void UI::menuCallback(Ref * pSender)
{
	auto pTempItem = (CCMenuItem*)pSender;

	Singleton::GetInstance()->ClearMode = pTempItem->getTag();

	switch (Singleton::GetInstance()->ClearMode)
	{
	case 3:
	{
		auto ToggleCheck_0 = dynamic_cast<MenuItemToggle*>(pSender);

		switch (ToggleCheck_0->getSelectedIndex())
		{
		case 0:
			Singleton::GetInstance()->BGM = true;
			break;
		case 1:
			Singleton::GetInstance()->BGM = false;
			break;
		}
	}
	break;
	case 4:
	{
		auto ToggleCheck_1 = dynamic_cast<MenuItemToggle*>(pSender);
		switch (ToggleCheck_1->getSelectedIndex())
		{
		case 0:
			Singleton::GetInstance()->SFX = true;
			break;
		case 1:
			Singleton::GetInstance()->SFX = false;
			break;
		}
	}
	break;
	case 5:
		Director::getInstance()->replaceScene(Credit::createScene());
		break;
	default:
		break;
	}
	Sound();
}

void UI::update(int a)
{
	switch (a)
	{
	case 0:
		Magazine_Num = 2;
		break;
	case 1:
		Magazine_Num = 8;
		break;
	case 2:
		Magazine_Num = 30;
		break;
	case 3:
		Magazine_Num = 25;
		break;
	case 4:
		Magazine_Num = 100;
		break;
	case 5:
		Magazine_Num = 1;
		break;
	case 6:
		Magazine_Num = 3;
		break;
	default:
		break;
	}
	Magazine_Label->setString(StringUtils::format("%d", Magazine_Num));
}

void UI::Hero_Update(int a)
{
	Health_bar->setTexture(StringUtils::format("UI/Health_bar_%d.png", a));
}

void UI::Magazine_Animation()
{
	auto animation = Animation::create();
	for (int i = 0; i < 4; i++)
	{
		animation->addSpriteFrameWithFile(StringUtils::format("UI/Magazine_Animation_%d.png", i));
	}
	animation->setDelayPerUnit(0.05f);
	auto animate = Animate::create(animation);
	Magazine->runAction(animate);
}

void UI::LifeImageCheck(int a)
{
	auto Clear_Background = Sprite::create("UI/InGame_Clear_Background.png");
	Clear_Background->setPosition(Vec2(640, 360));
	ClearLayer->addChild(Clear_Background);

	auto Background = Sprite::create("UI/Background.png");
	Background->setPosition(Vec2(Clear_Background->getContentSize().width / 2, Clear_Background->getContentSize().height / 2));
	Clear_Background->addChild(Background, -1);

	switch (a)
	{
	case 0:
	{
		auto Background_dead = Sprite::create("UI/Blood_Background.png");
		Background_dead->setPosition(Vec2(Clear_Background->getContentSize().width / 2, Clear_Background->getContentSize().height / 2));
		Clear_Background->addChild(Background_dead);

		auto Dead = Sprite::create("UI/Ingame_Dead.png");
		Dead->setOpacity(0.0f);//
		Dead->setPosition(Vec2(Clear_Background->getContentSize().width / 2, Clear_Background->getContentSize().height / 2));
		Dead->runAction(FadeIn::create(3.0f));
		Clear_Background->addChild(Dead);

		auto Restart = MenuItemImage::create("UI/Restart_on.png", "UI/Restart_off.png", "UI/Restart_off.png", CC_CALLBACK_1(UI::menuCallback, this));
		Restart->setTag(0);
		auto MainMenu = MenuItemImage::create("UI/MainMenu_on.png", "UI/MainMenu_off.png", "UI/MainMenu_off.png", CC_CALLBACK_1(UI::menuCallback, this));
		MainMenu->setTag(1);
		auto menu = Menu::create(Restart, MainMenu, NULL);
		menu->setPosition(Vec2(640, 360));
		menu->setVisible(false);
		menu->alignItemsHorizontally();
		menu->alignItemsHorizontallyWithPadding(520.0f);
		menu->runAction(Sequence::create(DelayTime::create(3.0f), Show::create(), NULL));
		ClearLayer->addChild(menu);
	}
		break;
	case 1:
	{
		auto Clear = Sprite::create("UI/Ingame_Clear_9.png");
		Clear->setPosition(Vec2(Clear_Background->getContentSize().width / 2, Clear_Background->getContentSize().height / 2));
		Clear_Background->addChild(Clear);

		auto animation = Animation::create();
		for (int i = 1; i < 10; i++)
		{
			animation->addSpriteFrameWithFile(StringUtils::format("UI/Ingame_Clear_%d.png", i));
		}
		animation->setDelayPerUnit(0.08f);
		auto animate = Animate::create(animation);
		Clear->runAction(Sequence::create(DelayTime::create(1.0f), animate, NULL));

		auto Space = Sprite::create();
		Space->setPosition(Vec2(830, 315));
		ClearLayer->addChild(Space);

		auto animation2 = Animation::create();
		for (int i = 0; i < 3; i++)
		{
			animation2->addSpriteFrameWithFile(StringUtils::format("UI/Clear_Light_%d.png", i));
		}
		animation2->setDelayPerUnit(0.08f);
		auto animate2 = Animate::create(animation2);

		Space->runAction(Sequence::create(DelayTime::create(1.72f), animate2, Hide::create(), NULL));

		auto Restart = MenuItemImage::create("UI/Restart_on.png", "UI/Restart_off.png", "UI/Restart_off.png", CC_CALLBACK_1(UI::menuCallback, this));
		Restart->setTag(0);
		auto MainMenu = MenuItemImage::create("UI/MainMenu_on.png", "UI/MainMenu_off.png", "UI/MainMenu_off.png", CC_CALLBACK_1(UI::menuCallback, this));
		MainMenu->setTag(1);
		auto menu = Menu::create(Restart, MainMenu, NULL);
		menu->setPosition(Vec2(640, 360));
		menu->alignItemsHorizontally();
		menu->alignItemsHorizontallyWithPadding(500.0f);
		ClearLayer->addChild(menu);
	}
	break;
	default:
		break;
	}
}

