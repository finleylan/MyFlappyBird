#include "OptionLayer.h"

bool OptionLayer::init()
{
	if(Layer::init())
	{
		/*auto dispatcher = Director::getInstance()->getEventDispatcher();
        auto listener = EventListenerTouchAllAtOnce::create();
        listener->onTouchesBegan = CC_CALLBACK_2(OptionLayer::onTouchesBegan, this);
        dispatcher->addEventListenerWithSceneGraphPriority(listener, this);*/

		auto listener=EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan=[this](const std::vector<Touch*>& touches, Event *event)
		{
			this->delegator->onTouch();
		};

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
		
		return true;
	}
	else 
	{
		return false;
	}
}

//void OptionLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
//{
//	this->delegator->onTouch();
//}