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

//��İ뾶
const int BIRD_RADIUS=15;
//ˮ�ܵĸ߶�
const int PIP_HEIGHT=320;
//ˮ�ܵĿ��
const int PIP_WIDTH=52;
//ˮ��ת���ٶ�
const float PIP_SHIFT_SPEED=80.0f;
//����ˮ��֮��ľ���
const int PIP_DISTANCE=100;
//ˮ�ܴ�ֱ����
const int PIP_INTERVAL=180;
//ͬһʱ����Ļ�ϳ��ֵ�ˮ�ܶ���
const int PIP_COUNT=2;
//ˮ�ܳ�������Ļ�ϵ����׼������
const int WAIT_DISTANCE=100;

//������Ϸ״̬
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