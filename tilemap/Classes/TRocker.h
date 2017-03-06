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
	//����ҡ�ˣ�ҡ��ͼƬ��ҡ�˱���ͼƬ����ʼ����  
	static TRocker* createTRocker(const char* rockerImageName, const char* rockerBGImageName, Point position);
	//����ҡ��  
	void startRocker(bool _isStopOther);
	//ֹͣҡ��
	void stopRocker();
	//���ÿ��Ƶľ���
	void setSprite(Sprite* sprite);
private:
	EventListenerTouchOneByOne* listener;
	void rockerInit(const char* rockerImageName, const char* rockerBGImageName, Point position);
	//�õ��뾶Ϊr��Բ���˶���һ���Ƕ�Ӧ��Ӧ��x,y����  
	Point getAnglePosition(float r, float angle);
	//�Ƿ�ɲ���ҡ��  
	bool isCanMove;
	//�õ�ҡ�����û�������ĽǶ�  
	float getRad(Point pos1, Point pos2);
	//ҡ�˱���������  
	Point rockerBGPosition;
	//ҡ�˱����İ뾶  
	float rockerBGR;
	//�����¼�  
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	//�ƶ�����
	void moveSprite(Vec2 touchPoint, Vec2 bgPoint);
	//
	CREATE_FUNC(TRocker);
};

