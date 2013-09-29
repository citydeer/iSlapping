//
//  GameScene.cpp
//  iSlapping
//
//  Created by Pang Zhenyu on 13-7-18.
//
//

#include "GameScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"


using namespace cocos2d;



#define BORDER_LEFT (135+m_fOffset)
#define BORDER_RIGHT (370+m_fOffset)
#define GOOD_LEFT (213+m_fOffset)
#define GOOD_RIGHT (296+m_fOffset)
#define PERFECT_LEFT (243+m_fOffset)
#define PERFECT_RIGHT (266+m_fOffset)
#define SHAKER_Y 295


CCScene* GameScene::scene()
{
	CCScene* scene = CCScene::create();
	
	GameScene* layer = GameScene::create();
	
	scene->addChild(layer);
	
	return scene;
}

GameScene::~GameScene()
{
	m_pShaker->release();
	m_pShadow->release();
}

bool GameScene::init()
{
	if (!CCLayer::init())
		return false;
	
	m_iHits = 0;
	m_iScore = 0;
	m_iStatus = 0;
	m_bHitInPreviousCircle = false;
	
	this->setTouchEnabled(true);
	
	CCSize ws = CCDirector::sharedDirector()->getWinSize();
	
	m_fOffset = (ws.width - 480) / 2.0;
	
	CCSprite* bg = CCSprite::create("bg.png");
	bg->setPosition(ccp(ws.width/2, ws.height/2));
	this->addChild(bg, 0);
	
	m_pShaker = CCSprite::create("hand.png");
	m_pShaker->retain();
	m_pShaker->setPosition(ccp(BORDER_LEFT, SHAKER_Y));
	this->addChild(m_pShaker, 2);
	
	m_pShadow = CCSprite::create("hand.png");
	m_pShadow->retain();
	m_pShadow->setVisible(false);
	this->addChild(m_pShadow, 1);
	
	this->startGame();
	
	return true;
}

void GameScene::startGame()
{
	m_iStatus = 1;
	m_iScore = 0;
	m_iHits = 0;
	
	// Set to YES in the first circle.
	m_bHitInPreviousCircle = true;
	
	m_pShaker->setPosition(ccp(BORDER_LEFT, SHAKER_Y));
	CCMoveTo* move = CCMoveTo::create(1, ccp(BORDER_RIGHT, SHAKER_Y));
	CCCallFuncN* moveEnded = CCCallFuncN::create(this, callfuncN_selector(GameScene::shakerMoveEnded));
	m_pShaker->runAction(CCSequence::create(move, moveEnded, NULL));
}

void GameScene::gameOver()
{
	m_iStatus = 0;
	m_pShaker->stopAllActions();
	this->addChild(GameOverScene::create(), 3);
}

void GameScene::shakerMoveEnded(CCNode* pNode)
{
	if (!m_bHitInPreviousCircle)
	{
		this->gameOver();
		return;
	}
	
	m_bHitInPreviousCircle = false;
	
	float nextTime = 0.2f;
	if (m_iHits < 80)
		nextTime = 1.0f - m_iHits/50.0f;
	
	CCMoveTo* move = NULL;
	if (m_pShaker->getPosition().x == BORDER_RIGHT)
		move = CCMoveTo::create(nextTime, ccp(BORDER_LEFT, SHAKER_Y));
	else
		move = CCMoveTo::create(nextTime, ccp(BORDER_RIGHT, SHAKER_Y));
	
	CCCallFuncN* moveEnded = CCCallFuncN::create(this, callfuncN_selector(GameScene::shakerMoveEnded));
	m_pShaker->runAction(CCSequence::create(move, moveEnded, NULL));
}

void GameScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	// If not in game, return.
	if (m_iStatus == 0)
		return;
	
	int x = m_pShaker->getPosition().x;
	
	if (x < GOOD_LEFT || x > GOOD_RIGHT)
	{
		// Not hit, game over
		this->gameOver();
	}
	else
	{
		if (x < PERFECT_LEFT || x >PERFECT_RIGHT)
			m_iScore += 50; // Good
		else
			m_iScore += 100; // Perfect
		
		m_iHits++;
		
		// Set hit flag
		m_bHitInPreviousCircle = true;
		
		// Show shaker's shadow
		m_pShadow->stopAllActions();
		m_pShadow->setPosition(ccp(x, SHAKER_Y));
		m_pShadow->setVisible(true);
		m_pShadow->runAction(CCFadeOut::create(0.3));
	}
	
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("slap.wav");
}




bool GameOverScene::init()
{
	if (!CCLayer::init())
		return false;
	
	CCSize ws = CCDirector::sharedDirector()->getWinSize();
	
	CCLayerColor* bg = CCLayerColor::create(ccc4(0, 0, 0, 128), 300, 200);
	bg->ignoreAnchorPointForPosition(false);
	bg->setPosition(ccp(ws.width/2, ws.height/2));
	this->addChild(bg, 0);
	
	CCMenuItemFont::setFontName("Marker Felt");
	CCMenuItemFont::setFontSize(30);
	
	CCMenuItem* restart = CCMenuItemFont::create("Restart", this, menu_selector(GameOverScene::onRestart));
	CCMenuItem* back = CCMenuItemFont::create("Back", this, menu_selector(GameOverScene::onBack));
	CCMenu* menu = CCMenu::create(restart, back, NULL);
	menu->alignItemsVertically();
	this->addChild(menu, 1);
	
	return true;
}

void GameOverScene::onRestart(cocos2d::CCObject *pSender)
{
	static_cast<GameScene*>(this->getParent())->startGame();
	this->removeFromParent();
}

void GameOverScene::onBack(cocos2d::CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(StartScene::scene());
}




