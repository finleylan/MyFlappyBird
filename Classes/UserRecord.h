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

	//�洢keyָ������ݵ�����xml�ļ�
	void saveIntegerToUserDefault(const char* key, int score);

	//��ȡ�洢��keyָ�������
	int readIntegerFromUserDefault(const char* key);

private:
	static UserRecord* shareUserRecord;
};

#endif