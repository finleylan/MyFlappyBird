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
	//С����Ӷ�����������Ӱ��
	void idle();
	//������Ӱ��
	void fly();
	//С������
	void die();
protected:
	//����֡����
	static Animation* createAnimation(const char* fmt,int count,float fps);

	void createBirdByRandom();
private:
	static BirdSprite* shareBirdSprite;

	bool changeState(ActionState state);

	Action* idleAction;
	Action* swingAction;

	ActionState currentStatus;

	//��������������
	string birdName;
	string birdNameFormat;

	//��¼��һ�ν�����Ϸ��ʱ��
	unsigned int isFirstTime;
};

#endif