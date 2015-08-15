#include "GameScene.h"
#include "BackgroundLayer.h"
#include "GameLayer.h"
#include "OptionLayer.h"
#include "StatusLayer.h"
bool GameScene::init()
{
	if(Scene::initWithPhysics())
	{
		//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		this->getPhysicsWorld()->setGravity(Vect(0,-900));
	}

	//Ìí¼Ó±³¾°
	auto backgroundLayer=BackgroundLayer::create();
	if(backgroundLayer)
	{
		this->addChild(backgroundLayer);
	}
	
	auto statusLayer=StatusLayer::create();

	//Ìí¼ÓÖ÷ÓÎÏ·²ã
	auto gameLayer = GameLayer::create();
	if(gameLayer) 
	{
		gameLayer->setPhyWorld(this->getPhysicsWorld());
		gameLayer->setDelegator(statusLayer);
		this->addChild(gameLayer);
	}

	//Ìí¼ÓÓÎÏ·×´Ì¬²ã
	if(statusLayer)
	{
		this->addChild(statusLayer);
	}

	//Ìí¼Ó¿ØÖÆ²ã
	auto optionLayer=OptionLayer::create();
	if(optionLayer)
	{
		optionLayer->setDelegator(gameLayer);
		this->addChild(optionLayer);
	}

	return true;
}

void GameScene::restart()
{
	this->removeAllChildrenWithCleanup(true);
	this->init();
}