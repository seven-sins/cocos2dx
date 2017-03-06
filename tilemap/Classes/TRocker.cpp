#include "TRocker.h"
USING_NS_CC;

void TRocker::setSprite(Sprite* sprite)
{
	this->sprite = sprite;
	// 初始化
	tAnimate = TAnimate::createTAnimate();
}
TRocker* TRocker::createTRocker(const char *rockerImageName, const char *rockerBGImageName, Point position)
{
	TRocker* layer = TRocker::create();
	if (layer)
	{
		layer->rockerInit(rockerImageName, rockerBGImageName, position);
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}
void TRocker::rockerInit(const char *rockerImageName, const char *rockerBGImageName, Point position)
{
	//添加摇杆背景图--->触点背景
	spRockerBG = Sprite::create(rockerBGImageName);
	spRockerBG->setVisible(false);
	spRockerBG->setPosition(position);
	spRockerBG->setScale(0.8, 0.8);
	addChild(spRockerBG, 0, tag_rockerBG);
	//添加摇杆上方那个可移动的图--->触点 
	Sprite* spRocker = Sprite::create(rockerImageName);
	spRocker->setVisible(false);
	spRocker->setScale(0.8, 0.8);
	spRocker->setPosition(position);
	addChild(spRocker, 1, tag_rocker);
	spRocker->setOpacity(130);
	//摇杆背景图坐标  
	rockerBGPosition = position;
	//摇杆背景图半径  
	rockerBGR = spRockerBG->getContentSize().width * 0.35;
	listener = EventListenerTouchOneByOne::create();
	// 绑定监听事件
	listener->onTouchBegan = CC_CALLBACK_2(TRocker::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TRocker::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TRocker::onTouchEnded, this);
	listener->setSwallowTouches(true);
}
//启动摇杆  
void TRocker::startRocker(bool _isStopOther)
{
	//精灵设置可见，设置监听  
	Sprite* rocker = (Sprite*)getChildByTag(tag_rocker);
	rocker->setVisible(true);
	Sprite* rockerBG = (Sprite*)getChildByTag(tag_rockerBG);
	rockerBG->setVisible(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
//停止摇杆  
void TRocker::stopRocker()
{
	//精灵设置不可见，取消监听  
	Sprite* rocker = (Sprite*)getChildByTag(tag_rocker);
	rocker->setVisible(false);
	Sprite* rockerBG = (Sprite*)getChildByTag(tag_rockerBG);
	rockerBG->setVisible(false);
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
}
//得到两坐标的角度值  
float TRocker::getRad(Point pos1, Point pos2)
{
	//得到两点的坐标x,y坐标值  
	float px1 = pos1.x;
	float py1 = pos1.y;
	float px2 = pos2.x;
	float py2 = pos2.y;
	//求出两边长度  
	float x = px2 - px1;
	float y = py1 - py2;
	//开方   与  几次方 公式  
	float xie = sqrt(pow(x, 2) + pow(y, 2));
	float cos = x / xie;
	//反余弦定理，知道两边长求角度：cos = 邻边/斜边  
	float rad = acos(cos);
	//当触屏Y坐标 <摇杆的Y坐标时，取反值  
	if (py1 > py2)
	{
		rad = -rad;
	}
	return rad;
}
//得到与角度对应的半径为r的圆上一坐标点  
Point TRocker::getAnglePosition(float r, float angle)
{
	return ccp(r*cos(angle), r*sin(angle));
}
void TRocker::moveSprite(Vec2 touchPoint, Vec2 bgPoint)
{
	// 点击位置 - 背景位置
	Vec2 diff = touchPoint - bgPoint;
	if (abs(diff.x) > abs(diff.y)){
		if (diff.x > 0){
			tAnimate->run(sprite, "zhaoyun", "right");
		}
		else{
			tAnimate->run(sprite, "zhaoyun", "left");
		}
	}
	else{
		if (diff.y > 0){
			tAnimate->run(sprite, "zhaoyun", "up");
		}
		else{
			tAnimate->run(sprite, "zhaoyun", "down");
		}
	}
}
bool TRocker::onTouchBegan(Touch *touch, Event *event)
{
	Sprite* sp = (Sprite*)getChildByTag(tag_rocker);
	//得到触屏点坐标  
	Vec2 point = touch->getLocation();
	//判断是否点击到sp这个精灵：boundingBox()精灵大小之内的所有坐标  
	if (sp->boundingBox().containsPoint(point))
	{
		isCanMove = true;
	}
	Vec2 bgPoint = spRockerBG->getPosition();
	
	// 开始精灵动画
	moveSprite(point, bgPoint);

	return true;
}
void TRocker::onTouchMoved(Touch *touch, Event *event)
{
	if (!isCanMove)
	{
		return;
	}
	Sprite* sp = (Sprite*)getChildByTag(tag_rocker);
	Vec2 point = touch->getLocation();
	//判断两个圆心的距离是否大于摇杆背景的半径  
	if (sqrt(pow(point.x - rockerBGPosition.x, 2) + pow(point.y - rockerBGPosition.y, 2)) >= rockerBGR)
	{
		//得到触点与摇杆背景圆心形成的角度  
		float angle = getRad(rockerBGPosition, point);
		//确保小圆运动范围在背景圆内  
		sp->setPosition(ccpAdd(getAnglePosition(rockerBGR, angle), ccp(rockerBGPosition.x, rockerBGPosition.y)));
	}
	else {
		//触点在背景圆内则跟随触点运动  
		sp->setPosition(point);
	}
	// 变更动画
	Vec2 bgPoint = spRockerBG->getPosition();
	moveSprite(point, bgPoint);
}
void TRocker::onTouchEnded(Touch *touch, Event *event)
{
	if (!isCanMove)
	{
		return;
	}
	// 停止精灵动画
	sprite->stopAllActions();
	Sprite* rocker = (Sprite*)getChildByTag(tag_rocker);
	Sprite* rockerBG = (Sprite*)getChildByTag(tag_rockerBG);
	rocker->stopAllActions();
	rocker->runAction(MoveTo::create(0.08, rockerBG->getPosition()));
	isCanMove = false;
}
