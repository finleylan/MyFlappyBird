#include "GameLayer.h"
#include "BackgroundLayer.h"
#include "AtlasLoader.h"
#include "UserRecord.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool GameLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	Size visiableSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->gameStatus=GAME_STATUS_READY;
	this->score=0;

	//添加鸟精灵
	this->bird=BirdSprite::getInstance();
	this->bird->createBird();
	this->bird->setOpacity(255);

	auto body=PhysicsBody::createCircle(BIRD_RADIUS);

	body->setDynamic(true);
	body->setLinearDamping(0.0f);
	body->setGravityEnable(false);

	this->bird->setPhysicsBody(body);

	this->bird->getPhysicsBody()->setCategoryBitmask(1);
	this->bird->getPhysicsBody()->setCollisionBitmask(1);
	this->bird->getPhysicsBody()->setContactTestBitmask(1);

	this->bird->setPosition(Vec2(origin.x + visiableSize.width*1/3 - 5,origin.y + visiableSize.height/2 + 5));
	this->bird->idle();
	this->addChild(this->bird);

	//添加地面
	this->groundNode=Node::create();
	float landHeight=BackgroundLayer::getLandHeight();

	auto groundBody=PhysicsBody::createBox(Size(288,landHeight),PHYSICSBODY_MATERIAL_DEFAULT,Vec2::ZERO);

	groundBody->setDynamic(false);
	groundBody->setLinearDamping(0.0f);
	this->groundNode->setPhysicsBody(groundBody);
	this->groundNode->setPosition(144,landHeight/2);

	this->groundNode->getPhysicsBody()->setCategoryBitmask(1);
	this->groundNode->getPhysicsBody()->setCollisionBitmask(1);
	this->groundNode->getPhysicsBody()->setContactTestBitmask(1);

	this->addChild(this->groundNode);

	//init land
	this->landSprite1=Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	this->landSprite1->setAnchorPoint(Vec2::ZERO);
	this->landSprite1->setPosition(Vec2::ZERO);
	this->addChild(this->landSprite1,30);

	this->landSprite2=Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	this->landSprite2->setAnchorPoint(Vec2::ZERO);
	this->landSprite2->setPosition(this->landSprite1->getContentSize().width-2.0f,0);
	this->addChild(this->landSprite2,30);

	shiftLand=schedule_selector(GameLayer::scrollLand);
	this->schedule(shiftLand,0.01f);

	this->scheduleUpdate();


	auto contactListener=EventListenerPhysicsContact::create();
	contactListener->onContactBegin=[this](PhysicsContact& contact)
	{
		this->gameOver();
	    return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener,this);

	//Android平台菜单返回键监听
	auto listener=EventListenerKeyboard::create();
	listener->onKeyReleased=[this](EventKeyboard::KeyCode keycode, Event *event)
	{
		switch (keycode)
		{
			//监听返回键
			case EventKeyboard::KeyCode::KEY_ESCAPE:
				Director::getInstance()->end();
				break;
			//监听menu键
			case EventKeyboard::KeyCode::KEY_MENU:
				break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	return true;

}



void GameLayer::scrollLand(float dt)
{
	this->landSprite1->setPositionX(this->landSprite1->getPositionX() - 2.0f);
	this->landSprite2->setPositionX(this->landSprite1->getPositionX() + this->landSprite1->getContentSize().width - 2.0f);
	if(this->landSprite2->getPositionX() == 0)
	{
		this->landSprite1->setPositionX(0);
	}

	//移动水管
	for(auto singlePip : this->pips)
	{
		singlePip->setPositionX(singlePip->getPositionX() - 2);
        if(singlePip->getPositionX() < -PIP_WIDTH)
		{
            singlePip->setTag(PIP_NEW);
            Size visibleSize = Director::getInstance()->getVisibleSize();
            singlePip->setPositionX(visibleSize.width);
            singlePip->setPositionY(this->getRandomHeight());
	    }
    }
}

void GameLayer::onTouch()
{
	if(this->gameStatus == GAME_STATUS_OVER)
	{
		return;
	}
	SimpleAudioEngine::getInstance()->playEffect("sfx_wing.ogg");
	if(this->gameStatus == GAME_STATUS_READY)
	{
		this->delegator->onGameStart();
		this->bird->fly();
		this->gameStatus=GAME_STATUS_START;
		this->createPips();
	}
	else if(this->gameStatus == GAME_STATUS_START)
	{
		this->bird->getPhysicsBody()->setVelocity(Vect(0,260));
	}
}

void GameLayer::rotateBird()
{
	float verticalSpeed = this->bird->getPhysicsBody()->getVelocity().y;
    this->bird->setRotation(-min(max(-90, (verticalSpeed*0.2 + 60)), 30));
}

void GameLayer::update(float delta)
{
	if (this->gameStatus == GAME_STATUS_START)
	{
        this->rotateBird();
		this->checkHit();
    }
}

void GameLayer::createPips() {
    // Create the pips
    for (int i = 0; i < PIP_COUNT; i++) 
	{
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Sprite *pipUp = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("pipe_up"));
        Sprite *pipDown = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("pipe_down"));
        Node *singlePip = Node::create();
        
        // bind to pair
        pipDown->setPosition(0, PIP_HEIGHT + PIP_DISTANCE);
		singlePip->addChild(pipDown, 0, DOWN_PIP);
        singlePip->addChild(pipUp, 0, UP_PIP);
        singlePip->setPosition(visibleSize.width + i*PIP_INTERVAL + WAIT_DISTANCE, this->getRandomHeight());
		
		auto body = PhysicsBody::create();
		auto shapeBoxDown = PhysicsShapeBox::create(pipDown->getContentSize(),PHYSICSSHAPE_MATERIAL_DEFAULT, Vec2(0, PIP_HEIGHT + PIP_DISTANCE));
		body->addShape(shapeBoxDown);
		body->addShape(PhysicsShapeBox::create(pipUp->getContentSize()));

		
		body->setCategoryBitmask(1);
		body->setCollisionBitmask(1);
		body->setContactTestBitmask(1);

		body->setDynamic(false);
		singlePip->setPhysicsBody(body);
        singlePip->setTag(PIP_NEW);
        
        this->addChild(singlePip);
        this->pips.push_back(singlePip);
    }
}

int GameLayer::getRandomHeight() 
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    return rand()%(int)(2*PIP_HEIGHT + PIP_DISTANCE - visibleSize.height);
}

void GameLayer::checkHit() 
{
    for(auto pip : this->pips)
	{
		if (pip->getTag() == PIP_NEW) 
		{
            if (pip->getPositionX() < this->bird->getPositionX()) 
			{
				SimpleAudioEngine::getInstance()->playEffect("sfx_point.ogg");
                this->score ++;
                this->delegator->onGamePlaying(this->score);
                pip->setTag(PIP_PASS);
            }
        }
    }
}

void GameLayer::gameOver() 
{
    if(this->gameStatus == GAME_STATUS_OVER)
	{
        return;
    }
	SimpleAudioEngine::getInstance()->playEffect("sfx_hit.ogg");
	//get the best score
	int bestScore = UserRecord::getInstance()->readIntegerFromUserDefault("best_score");
	//update the best score
	if(this->score > bestScore)
	{
		UserRecord::getInstance()->saveIntegerToUserDefault("best_score",this->score);
	}
	this->delegator->onGameEnd(this->score, bestScore);
	this->unschedule(shiftLand);
	SimpleAudioEngine::getInstance()->playEffect("sfx_die.ogg");
	this->bird->die();
	this->bird->setRotation(-90);
	this->birdSpriteFadeOut();
	this->gameStatus = GAME_STATUS_OVER;
}

void GameLayer::birdSpriteFadeOut()
{
	FadeOut* animation = FadeOut::create(1.5);
	CallFunc* animationDone = CallFunc::create(bind(&GameLayer::birdSpriteRemove,this));
	Sequence* sequence = Sequence::createWithTwoActions(animation,animationDone);
	this->bird->stopAllActions();
	this->bird->runAction(sequence);
}

void GameLayer::birdSpriteRemove()
{
	this->bird->setRotation(0);
	this->removeChild(this->bird);
}