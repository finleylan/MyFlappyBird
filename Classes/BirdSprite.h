#ifndef _BIRD_SPRITE_H_
#define _BIRD_SPRITE_H_
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
typedef enum
{
	ACTION_STATE_IDLE,
	ACTION_STATE_FLY,
	ACTION_STATE_DIE
} ActionState;

const int BIRD_SPRITE_TAG=10003;

class BirdSprite:public Sprite
{
public:
	static BirdSprite* getInstance();
	
	virtual bool init();

	bool createBird();
	//小鸟翅膀挥动，不受重力影响
	void idle();
	//受重力影响
	void fly();
	//小鸟死亡
	void die();
protected:
	//创建帧动画
	static Animation* createAnimation(const char* fmt,int count,float fps);

	void createBirdByRandom();
private:
	static BirdSprite* shareBirdSprite;

	bool changeState(ActionState state);

	Action* idleAction;
	Action* swingAction;

	ActionState currentStatus;

	//鸟的名字随机创建
	string birdName;
	string birdNameFormat;

	//记录第一次进入游戏的时间
	unsigned int isFirstTime;
};

#endif