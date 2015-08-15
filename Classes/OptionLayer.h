#ifndef _OPTION_LAYER_H_
#define _OPTION_LAYER_H_
#include "cocos2d.h"
USING_NS_CC;

class OptionDelegate
{
public:
    virtual void onTouch() = 0;
};

class OptionLayer:public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(OptionLayer);
    
    // override
  //  void onTouchesBegan(const std::vector<Touch*>& touches, Event *event);
    
    CC_SYNTHESIZE(OptionDelegate*, delegator, Delegator);
};

#endif