#ifndef _BACKGROUND_LAYER_H_
#define _BACKGROUND_LAYER_H_
#include "BirdSprite.h"
#include "cocos2d.h"
USING_NS_CC;

class BackgroundLayer:public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(BackgroundLayer);

	static float getLandHeight();


};

#endif