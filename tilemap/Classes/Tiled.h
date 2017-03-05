#pragma once
#include "cocos2d.h"
#include "Base.h"

class Tiled : public cocos2d::Layer
{
	// 成员变量
	cocos2d::Sprite* player;
	cocos2d::TMXTiledMap* tileMap;
	cocos2d::TMXLayer* collidable;
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(Tiled);
	// 
private:
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual bool init();
	virtual void onEnter();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	// 从当前像素坐标获得tile coord
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	// 获得精灵位置
	void setPlayerPosition(cocos2d::Vec2 position);
	// 设置视点
	void setViewPointCenter(cocos2d::Vec2 position);
	// test
	void test();
};

