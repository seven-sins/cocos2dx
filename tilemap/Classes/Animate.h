#pragma once
#include "cocos2d.h"

class Animate : public cocos2d::Layer
{
	cocos2d::Sprite _sprite;
public:
	CREATE_FUNC(Animate);
	// sprite: 精灵
	// sprite: 精灵名称
	// direction: 方向
	void run(cocos2d::Sprite sprite, const char* spriteName, const char* direction);
};

