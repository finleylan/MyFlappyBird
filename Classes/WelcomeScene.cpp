#include "WelcomeScene.h"
#include "AtlasLoader.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

Scene* Welcome::createScene()
{
	auto scene=Scene::create();
	auto layer=Welcome::create();
	scene->addChild(layer);

	return scene;
}

bool Welcome::init()
{
	if(!Layer::init())
	{
		return false;
	}
	Size visiableSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	//����������졢ҹ����ͼƬ
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
	
	//�����Ϸ����
	auto title  = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("title"));
	title->setPosition(Vec2(origin.x + visiableSize.width/2 , (visiableSize.height * 5) / 7));
	this->addChild(title);

	//���С��
	this->bird = BirdSprite::getInstance();
	this->bird->createBird();
	this->bird->setTag(BIRD_SPRITE_TAG);
	this->bird->setPosition(Point(origin.x + visiableSize.width / 2,origin.y + visiableSize.height*3/5 - 10));
	this->bird->idle();
	this->addChild(this->bird);

	//��ӿ�ʼ��ť
	auto startButton=Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	auto activeStartButton = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	activeStartButton->setPositionY(5);
	auto menuItem=MenuItemSprite::create(startButton,activeStartButton,NULL,CC_CALLBACK_1(Welcome::menuStartCallback, this));
	menuItem->setPosition(Vec2(origin.x + visiableSize.width/2 ,origin.y + visiableSize.height*2/5));

	auto menu=Menu::create(menuItem,NULL);
	menu->setPosition(Vec2(origin.x ,origin.y));
	this->addChild(menu,1);

	//���½��
	this->land1 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	this->land1->setAnchorPoint(Vec2::ZERO);
	this->land1->setPosition(Vec2::ZERO);
	this->addChild(this->land1);

	this->land2 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	this->land2->setAnchorPoint(Vec2::ZERO);
	this->land2->setPosition(Vec2(this->land1->getContentSize().width - 2.0f, 0));
	this->addChild(this->land2);

	this->schedule(schedule_selector(Welcome::scrollLand), 0.01f);

	//Androidƽ̨�˵����ؼ�����
	auto listener=EventListenerKeyboard::create();
	listener->onKeyReleased=[this](EventKeyboard::KeyCode keycode, Event *event)
	{
		switch (keycode)
		{
			//�������ؼ�
			case EventKeyboard::KeyCode::KEY_ESCAPE:
				Director::getInstance()->end();
				break;
			//����menu��
			case EventKeyboard::KeyCode::KEY_MENU:
				break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}

void Welcome::menuStartCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	this->removeChildByTag(BIRD_SPRITE_TAG);
	auto scene=GameScene::create();
	auto transition=TransitionFade::create(1,scene);
	Director::getInstance()->replaceScene(transition);
}

void Welcome::scrollLand(float dt)
{
	this->land1->setPositionX(this->land1->getPositionX() - 2.0f);
	this->land2->setPositionX(this->land1->getPositionX() + this->land1->getContentSize().width - 2.0f);

	if(this->land2->getPositionX() == 0)
	{
		this->land1->setPositionX(0);
	}
}