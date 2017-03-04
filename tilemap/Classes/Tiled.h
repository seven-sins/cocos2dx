#pragma once
#include "cocos2d.h"
#include "Base.h"

class Tiled : public cocos2d::Layer
{
	// ��Ա����
	cocos2d::Sprite* player;
	cocos2d::TMXTiledMap* tileMap;
	cocos2d::TMXLayer* collidable;
public:
	static cocos2d::Scene* createScene();
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(Tiled);
	// 
	virtual bool init();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	// �ӵ�ǰ����������tile coord
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	// ��þ���λ��
	void setPlayerPosition(cocos2d::Vec2 position);
	// �����ӵ�
	void setViewPointCenter(cocos2d::Vec2 position);
};

