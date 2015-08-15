#ifndef _USER_RECORD_H_
#define _USER_RECORD_H_
#include "cocos2d.h"
USING_NS_CC;

class UserRecord:public Ref
{
public:

	virtual bool init();

	static UserRecord* getInstance();

	static void destoryInstance();

	//存储key指向的数据到本地xml文件
	void saveIntegerToUserDefault(const char* key, int score);

	//获取存储的key指向的数据
	int readIntegerFromUserDefault(const char* key);

private:
	static UserRecord* shareUserRecord;
};

#endif