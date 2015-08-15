#include "BackgroundLayer.h"
#include "AtlasLoader.h"
#include "BirdSprite.h"
bool BackgroundLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	Sprite* background=nullptr;
	float i=CCRANDOM_0_1();
	if(i < 0.5)
	{
		background=Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bg_night"));
	}
	else
	{
		background=Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bg_day"));
	}
	background->setAnchorPoint(Vec2::ZERO);
	background->setPosition(Vec2::ZERO);
	this->addChild(background);

	return true;
}

float BackgroundLayer::getLandHeight()
{
	return Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"))->getContentSize().height;
}