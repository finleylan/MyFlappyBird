#ifndef _WELCOME_SCENE_H_
#define _WELCOME_SCENE_H_
#include "cocos2d.h"
#include "BirdSprite.h"
USING_NS_CC;

class Welcome:public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Welcome);
private:
	void menuStartCallback(Ref* pSender);
	void scrollLand(float dt);
	Sprite* land1;
	Sprite* land2;
	BirdSprite* bird;
};

#endif