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
	
	CCMenuItemFont* startMi = CCMenuItemFont::create("Start", this, menu_selector(StartScene::onStart));
	CCMenuItemFont* optionMi = CCMenuItemFont::create("Option", this, menu_selector(StartScene::onOption));
	CCMenuItemFont* helpMi = CCMenuItemFont::create("Help", this, menu_selector(StartScene::onHelp));
	
	CCMenu* pMenu = CCMenu::create(startMi, optionMi, helpMi);
	pMenu->alignItemsVertically();
	this->addChild(pMenu);
	
	return true;
}


void StartScene::onStart(CCObject* pSender)
{
	printf("Start\n");
}

void StartScene::onOption(CCObject* pSender)
{
	printf("Option\n");
}

void StartScene::onHelp(CCObject* pSender)
{
	printf("Help\n");
}



