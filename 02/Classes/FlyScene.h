#pragma once

#include "cocos2d.h"
#include "ActionScene.h"

typedef enum
{
	PLACE_TAG = 102,
	FLIPX_TAG = 103,
	FLIPY_TAG = 104,
	HIDE_TAG = 105,
	TOGGLE_TAG = 106
} ActionTypes;

class FlyScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	virtual bool init();

	void placeCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(FlyScene);
};
