#pragma once
#include "cocos2d.h"

class Animate : public cocos2d::Layer
{
	cocos2d::Sprite _sprite;
public:
	CREATE_FUNC(Animate);
	// sprite: ����
	// sprite: ��������
	// direction: ����
	void run(cocos2d::Sprite sprite, const char* spriteName, const char* direction);
};

