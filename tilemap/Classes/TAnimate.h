#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class TAnimate : public Layer
{
	bool isStop;
public:
	static TAnimate* createTAnimate();
	// sprite: 精灵
	// sprite: 精灵名称
	// direction: 方向
	void run(Sprite* sprite, const char* spriteName, const char* direction);
private:
	CREATE_FUNC(TAnimate);
};

