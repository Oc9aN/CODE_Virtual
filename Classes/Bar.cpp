#include "Bar.h"


UIProgressBar::UIProgressBar(Layer* layer)
{
	ProgressLayer = Layer::create();
	ProgressLayer->setAnchorPoint(Vec2(0.0f, 0.5f));
	layer->addChild(ProgressLayer);
}

//!< 0.0f~1.0f
void UIProgressBar::SetPercentage(float fPercent)
{
	if (foregroundSprite != nullptr)
	{
		foregroundSprite->setScaleX(fPercent);
	}
}

void UIProgressBar::SetPosition(Vec2 vPos)
{
	ProgressLayer->setPosition(vPos);
}

void UIProgressBar::SetScale(float x, float y)
{
	ProgressLayer->setScale(x, y);
}

void UIProgressBar::SetForegroundSprite(Sprite* foreSprite)
{
	foregroundSprite = foreSprite;
	foregroundSprite->setAnchorPoint(Vec2(0.0f, 0.5f));
	ProgressLayer->addChild(foregroundSprite,2);
	SetPercentage(1.0f);
}

void UIProgressBar::SetBackgroundSprite(Sprite* backSprite)
{
	backgroundSprite = backSprite;
	backgroundSprite->setAnchorPoint(Vec2(0.0f, 0.5f));
	ProgressLayer->addChild(backgroundSprite, 1);
}

void UIProgressBar::SetmidgroundSprite(Sprite * midSprite)
{
	midgroundSprite = midSprite;
	midgroundSprite->setAnchorPoint(Vec2(0.0f, 0.5f));
	ProgressLayer->addChild(midgroundSprite, 0);
}

void UIProgressBar::Remove()
{
	ProgressLayer->removeFromParent();
}