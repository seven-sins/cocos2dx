#pragma once

#include "cocos2d.h"

class ActionScene : public cocos2d::Layer
{
	cocos2d::Sprite* planSprite;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onEnter();

	int flag;

	bool hidden;

	void goCallback(cocos2d::Ref* pSender);
	void backCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(ActionScene);

};
