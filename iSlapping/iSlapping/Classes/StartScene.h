//
//  StartScene.h
//  iSlapping
//
//  Created by Pang Zhenyu on 13-7-18.
//
//

#ifndef __iSlapping__StartScene__
#define __iSlapping__StartScene__

#include "cocos2d.h"


class StartScene : public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene* scene();
	
	virtual bool init();
	
	void menuItemCallback(CCObject* pSender);
	
	CREATE_FUNC(StartScene);
};

#endif /* defined(__iSlapping__StartScene__) */
