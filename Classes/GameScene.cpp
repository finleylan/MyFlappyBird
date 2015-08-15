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

	//��ӱ���
	auto backgroundLayer=BackgroundLayer::create();
	if(backgroundLayer)
	{
		this->addChild(backgroundLayer);
	}
	
	auto statusLayer=StatusLayer::create();

	//�������Ϸ��
	auto gameLayer = GameLayer::create();
	if(gameLayer) 
	{
		gameLayer->setPhyWorld(this->getPhysicsWorld());
		gameLayer->setDelegator(statusLayer);
		this->addChild(gameLayer);
	}

	//�����Ϸ״̬��
	if(statusLayer)
	{
		this->addChild(statusLayer);
	}

	//��ӿ��Ʋ�
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