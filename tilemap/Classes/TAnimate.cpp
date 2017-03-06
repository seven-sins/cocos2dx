#include "TAnimate.h"
USING_NS_CC;

TAnimate* TAnimate::createTAnimate()
{
	TAnimate* tAnimate = TAnimate::create();
	if (tAnimate)
	{
		tAnimate->isStop = false;
		return tAnimate;
	}
	CC_SAFE_DELETE(tAnimate);
	return NULL;
}
void TAnimate::run(Sprite* sprite, const char* spriteName, const char* direction)
{
	if (!isStop)
	{
		return;
	}
	sprite->stopAllActions();
	// ��������
	Animation* animation = Animation::create();
	for (int i = 1; i <= 3; i++){
		char filePath[100] = { 0 };
		sprintf(filePath, "sprite/%s/%s%s0%d.png", spriteName, spriteName, direction, i);
		animation->addSpriteFrameWithFile(filePath);
	}
	animation->setLoops(-1); // ����ѭ��
	animation->setDelayPerUnit(0.15f);
	animation->setRestoreOriginalFrame(true);
	Animate* animate = Animate::create(animation);
	sprite->runAction(animate);

	isStop = true;
}


