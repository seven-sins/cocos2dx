#pragma once
#include "cocos2d.h"
#include "TAnimate.h"
using namespace cocos2d;

typedef enum{
	tag_rocker,
	tag_rockerBG
}tagForTRocker;
class TRocker : public Layer
{
	Sprite* sprite;
	TAnimate* tAnimate;
	Sprite* spRockerBG;
	int moveTag;
public:
	//创建摇杆，摇杆图片，摇杆背景图片，起始坐标  
	static TRocker* createTRocker(const char* rockerImageName, const char* rockerBGImageName, Point position);
	//启动摇杆  
	void startRocker(bool _isStopOther);
	//停止摇杆
	void stopRocker();
	//设置控制的精灵
	void setSprite(Sprite* sprite);
private:
	EventListenerTouchOneByOne* listener;
	void rockerInit(const char* rockerImageName, const char* rockerBGImageName, Point position);
	//得到半径为r的圆周运动上一个角度应对应的x,y坐标  
	Point getAnglePosition(float r, float angle);
	//是否可操作摇杆  
	bool isCanMove;
	//得到摇杆与用户触屏点的角度  
	float getRad(Point pos1, Point pos2);
	//摇杆背景的坐标  
	Point rockerBGPosition;
	//摇杆背景的半径  
	float rockerBGR;
	//触屏事件  
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	//移动精灵
	void moveSprite(Vec2 touchPoint, Vec2 bgPoint);
	//
	CREATE_FUNC(TRocker);
};

