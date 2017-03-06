#pragma once
#include "cocos2d.h"
#include "Base.h"
#include "TRocker.h"
using namespace cocos2d;

class Tiled : public Layer
{
	// 成员变量
	Sprite* player;
	TMXTiledMap* tileMap;
	TMXLayer* collidable;
public:
	static Scene* createScene();
	CREATE_FUNC(Tiled);
	// 
private:
	void menuCloseCallback(Ref* pSender);
	virtual bool init();
	virtual void onEnter();
	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch* touch, Event* unused_event);
	virtual void onTouchMoved(Touch* touch, Event* unused_event);
	// 从当前像素坐标获得tile coord
	Vec2 tileCoordFromPosition(Vec2 position);
	// 获得精灵位置
	void setPlayerPosition(Vec2 position);
	// 设置视点
	void setViewPointCenter(Vec2 position);
	// test
	void test();
};

