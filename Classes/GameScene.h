#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_
#include "cocos2d.h"
USING_NS_CC;

class GameScene:public Scene
{
public:
	virtual bool init();

	CREATE_FUNC(GameScene);

	void restart();
};

#endif