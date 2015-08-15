#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_
#include "cocos2d.h"
#include "BirdSprite.h"
#include "OptionLayer.h"
USING_NS_CC;

#define min(X,Y) ((X) < (Y) ? (X) : (Y))
#define max(X,Y) ((X) > (Y) ? (X) : (Y))

const int UP_PIP=21;
const int DOWN_PIP=12;
const int PIP_PASS=30;
const int PIP_NEW=31;

//鸟的半径
const int BIRD_RADIUS=15;
//水管的高度
const int PIP_HEIGHT=320;
//水管的宽度
const int PIP_WIDTH=52;
//水管转换速度
const float PIP_SHIFT_SPEED=80.0f;
//上下水管之间的距离
const int PIP_DISTANCE=100;
//水管垂直距离
const int PIP_INTERVAL=180;
//同一时间屏幕上出现的水管对数
const int PIP_COUNT=2;
//水管出现在屏幕上的玩家准备距离
const int WAIT_DISTANCE=100;

//定义游戏状态
typedef enum _game_status
{
	GAME_STATUS_READY=1,
	GAME_STATUS_START,
	GAME_STATUS_OVER
} GameStatus;

class StatusDelegate
{
public:
	virtual void onGameStart()=0;
	
	virtual void onGamePlaying(int score)=0;

	virtual void onGameEnd(int curScore,int bestScore)=0;
};

class GameLayer:public Layer,public OptionDelegate
{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);

	CC_SYNTHESIZE(StatusDelegate*,delegator,Delegator);

	void onTouch();
	
	void setPhyWorld(PhysicsWorld* world){this->world=world;}

	void update(float delta);
private:
	void rotateBird();

	void createPips();

	int getRandomHeight();

	void checkHit();

	void birdSpriteFadeOut();

	void birdSpriteRemove();

	PhysicsWorld* world;

	GameStatus gameStatus;

	int score;

	BirdSprite* bird;

	Node* groundNode;

	vector<Node*> pips;

	Sprite *landSprite1, *landSprite2;

	SEL_SCHEDULE shiftLand;

	void scrollLand(float dt);

//	bool onContactBegin(PhysicsContact& contact);

	void gameOver();
};

#endif