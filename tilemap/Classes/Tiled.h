#pragma once
#include "cocos2d.h"
#include "Base.h"
#include "TRocker.h"
using namespace cocos2d;

class Tiled : public Layer
{
	// ��Ա����
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
	// �ӵ�ǰ����������tile coord
	Vec2 tileCoordFromPosition(Vec2 position);
	// ��þ���λ��
	void setPlayerPosition(Vec2 position);
	// �����ӵ�
	void setViewPointCenter(Vec2 position);
	// test
	void test();
};

