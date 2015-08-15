#ifndef _ATLAS_LOADER_H_
#define _ATLAS_LOADER_H_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

typedef struct _atlas
{
	char name[255];
	int width;
	int height;
	Point start;
	Point end;
} Atlas;

class AtlasLoader
{
public:
	static AtlasLoader* getInstance();

	static void destroyInstance();

	void loadAtlas(string filename);
	//可用异步方法载入纹理
	void loadAtlas(string filename,Texture2D* texture);

	SpriteFrame* getSpriteFrameByName(string name);
//protected:
	//AtlasLoader();

	virtual bool init();

	static AtlasLoader* sharedAtlasLoader;

	Map<std::string,SpriteFrame*> _spriteFrames;
};

#endif