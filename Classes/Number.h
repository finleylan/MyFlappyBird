#ifndef _NUMBER_H_
#define _NUMBER_H_
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

typedef enum _gravity
{
	GRAVITY_CENTER=1,
	GRAVITY_LEFT,
	GRAVITY_RIGHT
} Gravity;

//两个数字之间的距离
const int NumberInterval=4;

class NumberSeries:public Ref
{
public:
	virtual bool init();
	CREATE_FUNC(NumberSeries);

	void loadNumber(const char *fmt, int base=0);

	SpriteFrame* at(int index);
private:
	Vector<SpriteFrame*> numberSeries;
};

class Number
{
public:
	virtual bool init();

	static Number* getInstance();

	static void destroyInstance();

	virtual bool loadNumber(const char *name, const char *fmt, int base=0);

	Node* convert(const char* name, int number, Gravity gravity=GRAVITY_CENTER);

private:
	Map<string, NumberSeries*> numberContainer;

	static Number* sharedNumber;
};

#endif

