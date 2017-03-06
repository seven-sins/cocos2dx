#include "TRocker.h"
USING_NS_CC;

void TRocker::setSprite(Sprite* sprite)
{
	this->sprite = sprite;
	// ��ʼ��
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
	//���ҡ�˱���ͼ--->���㱳��
	spRockerBG = Sprite::create(rockerBGImageName);
	spRockerBG->setVisible(false);
	spRockerBG->setPosition(position);
	spRockerBG->setScale(0.8, 0.8);
	addChild(spRockerBG, 0, tag_rockerBG);
	//���ҡ���Ϸ��Ǹ����ƶ���ͼ--->���� 
	Sprite* spRocker = Sprite::create(rockerImageName);
	spRocker->setVisible(false);
	spRocker->setScale(0.8, 0.8);
	spRocker->setPosition(position);
	addChild(spRocker, 1, tag_rocker);
	spRocker->setOpacity(130);
	//ҡ�˱���ͼ����  
	rockerBGPosition = position;
	//ҡ�˱���ͼ�뾶  
	rockerBGR = spRockerBG->getContentSize().width * 0.35;
	listener = EventListenerTouchOneByOne::create();
	// �󶨼����¼�
	listener->onTouchBegan = CC_CALLBACK_2(TRocker::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TRocker::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TRocker::onTouchEnded, this);
	listener->setSwallowTouches(true);
}
//����ҡ��  
void TRocker::startRocker(bool _isStopOther)
{
	//�������ÿɼ������ü���  
	Sprite* rocker = (Sprite*)getChildByTag(tag_rocker);
	rocker->setVisible(true);
	Sprite* rockerBG = (Sprite*)getChildByTag(tag_rockerBG);
	rockerBG->setVisible(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
//ֹͣҡ��  
void TRocker::stopRocker()
{
	//�������ò��ɼ���ȡ������  
	Sprite* rocker = (Sprite*)getChildByTag(tag_rocker);
	rocker->setVisible(false);
	Sprite* rockerBG = (Sprite*)getChildByTag(tag_rockerBG);
	rockerBG->setVisible(false);
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
}
//�õ�������ĽǶ�ֵ  
float TRocker::getRad(Point pos1, Point pos2)
{
	//�õ����������x,y����ֵ  
	float px1 = pos1.x;
	float py1 = pos1.y;
	float px2 = pos2.x;
	float py2 = pos2.y;
	//������߳���  
	float x = px2 - px1;
	float y = py1 - py2;
	//����   ��  ���η� ��ʽ  
	float xie = sqrt(pow(x, 2) + pow(y, 2));
	float cos = x / xie;
	//�����Ҷ���֪�����߳���Ƕȣ�cos = �ڱ�/б��  
	float rad = acos(cos);
	//������Y���� <ҡ�˵�Y����ʱ��ȡ��ֵ  
	if (py1 > py2)
	{
		rad = -rad;
	}
	return rad;
}
//�õ���Ƕȶ�Ӧ�İ뾶Ϊr��Բ��һ�����  
Point TRocker::getAnglePosition(float r, float angle)
{
	return ccp(r*cos(angle), r*sin(angle));
}
void TRocker::moveSprite(Vec2 touchPoint, Vec2 bgPoint)
{
	// ���λ�� - ����λ��
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
	//�õ�����������  
	Vec2 point = touch->getLocation();
	//�ж��Ƿ�����sp������飺boundingBox()�����С֮�ڵ���������  
	if (sp->boundingBox().containsPoint(point))
	{
		isCanMove = true;
	}
	Vec2 bgPoint = spRockerBG->getPosition();
	
	// ��ʼ���鶯��
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
	//�ж�����Բ�ĵľ����Ƿ����ҡ�˱����İ뾶  
	if (sqrt(pow(point.x - rockerBGPosition.x, 2) + pow(point.y - rockerBGPosition.y, 2)) >= rockerBGR)
	{
		//�õ�������ҡ�˱���Բ���γɵĽǶ�  
		float angle = getRad(rockerBGPosition, point);
		//ȷ��СԲ�˶���Χ�ڱ���Բ��  
		sp->setPosition(ccpAdd(getAnglePosition(rockerBGR, angle), ccp(rockerBGPosition.x, rockerBGPosition.y)));
	}
	else {
		//�����ڱ���Բ������津���˶�  
		sp->setPosition(point);
	}
	// �������
	Vec2 bgPoint = spRockerBG->getPosition();
	moveSprite(point, bgPoint);
}
void TRocker::onTouchEnded(Touch *touch, Event *event)
{
	if (!isCanMove)
	{
		return;
	}
	// ֹͣ���鶯��
	sprite->stopAllActions();
	Sprite* rocker = (Sprite*)getChildByTag(tag_rocker);
	Sprite* rockerBG = (Sprite*)getChildByTag(tag_rockerBG);
	rocker->stopAllActions();
	rocker->runAction(MoveTo::create(0.08, rockerBG->getPosition()));
	isCanMove = false;
}
