#include "UserRecord.h"

bool UserRecord::init()
{
	return true;
}

UserRecord* UserRecord::shareUserRecord=nullptr;

UserRecord* UserRecord::getInstance()
{
	if(shareUserRecord==NULL)
	{
		shareUserRecord=new UserRecord();
		if(!shareUserRecord->init())
		{
			delete shareUserRecord;
			shareUserRecord=NULL;
		}
	}
	return shareUserRecord;
}

void UserRecord::destoryInstance()
{
	CC_SAFE_DELETE(shareUserRecord);
}

void UserRecord::saveIntegerToUserDefault(const char* key, int score)
{
	UserDefault::getInstance()->setIntegerForKey(key,score);
}

int UserRecord::readIntegerFromUserDefault(const char* key)
{
	int score=UserDefault::getInstance()->getIntegerForKey(key);
	return score;
}