//
//  StartScene.cpp
//  iSlapping
//
//  Created by Pang Zhenyu on 13-7-18.
//
//

#include "StartScene.h"

using namespace cocos2d;


CCScene* StartScene::scene()
{
	CCScene* scene = CCScene::create();
	
	StartScene* layer = StartScene::create();
	
	scene->addChild(layer);
	
	return scene;
}


bool StartScene::init()
{
	if (!CCLayer::init())
		return false;
	
	CCMenuItemFont::setFontName("Arial");
	CCMenuItemFont::setFontSize(25);
	
	CCMenuItemFont* startMi = CCMenuItemFont::create("Start", this, menu_selector(StartScene::menuItemCallback));
	startMi->setTag(0);
	CCMenuItemFont* optionMi = CCMenuItemFont::create("Option", this, menu_selector(StartScene::menuItemCallback));
	optionMi->setTag(1);
	CCMenuItemFont* helpMi = CCMenuItemFont::create("Help", this, menu_selector(StartScene::menuItemCallback));
	helpMi->setTag(2);
	
	CCMenu* pMenu = CCMenu::create(startMi, optionMi, helpMi);
	pMenu->alignItemsVertically();
	this->addChild(pMenu);
	
	return true;
}


void StartScene::menuItemCallback(CCObject* pSender)
{
	CCNode* pItem = dynamic_cast<CCNode*>(pSender);
	int tag = (pItem ? pItem->getTag() : -1);
	printf("Tap menu: %d\n", tag);
}


