#include "Tiled.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* Tiled::createScene()
{
	auto scene = Scene::create();
	auto layer = Tiled::create();
	scene->addChild(layer);

	return scene;
}

bool Tiled::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	return true;
}
void Tiled::onEnter()
{
	// ���ص�ͼ
	tileMap = TMXTiledMap::create("map/snow.tmx");
	this->addChild(tileMap, 0, 100);
	// ��ȡ������
	TMXObjectGroup* group = tileMap->getObjectGroup("object");
	ValueMap spPoint = group->getObject("zhaoyun");
	float x = spPoint["x"].asFloat();
	float y = spPoint["y"].asFloat();
	// ��Ӿ���
	player = Sprite::create("zhaoyun.png");
	float spriteWidth = Base::getInstance()->getSpriteWidth(); // ������
	float spriteHeight = Base::getInstance()->getSpriteHeight(); // ����߶�
	float tileWidth = tileMap->getTileSize().width; // tile size
	player->setContentSize(Size(spriteWidth, spriteHeight)); // ���þ����С
	player->setPosition(Vec2(x + tileWidth / 2, y + tileWidth / 2));
	this->addChild(player, 2, 200);
	this->setViewPointCenter(player->getPosition());
	// ��ȡ��ײ��
	collidable = tileMap->getLayer("collision");
	collidable->setVisible(false);
	// ����¼���Ӧ
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	//
	Layer::onEnter();
}
void Tiled::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}

bool Tiled::onTouchBegan(Touch* touch, Event* unused_event)
{

	return true;
}
void Tiled::onTouchEnded(Touch* touch, Event* unused_event)
{
	// ���openGL����
	Vec2 tochLocation = touch->getLocation();
	// ת��Ϊģ������
	tochLocation = this->convertToNodeSpace(tochLocation);
	Vec2 playerPos = player->getPosition();
	Vec2 diff = tochLocation - playerPos;

	if (abs(diff.x) > abs(diff.y)){
		if (diff.x > 0){
			playerPos.x += (tileMap->getTileSize().width);
			player->runAction(FlipX::create(false));
		}
		else{
			playerPos.x -= tileMap->getTileSize().width;
			player->runAction(FlipX::create(true));
		}
	}
	else{
		if (diff.y > 0){
			playerPos.y += tileMap->getTileSize().height;
		}
		else{
			playerPos.y -= tileMap->getTileSize().height;
		}
	}
	//
	this->setPlayerPosition(playerPos);
}
void Tiled::onTouchMoved(Touch* touch, Event* unused_event)
{

}
// �ӵ�ǰ����������tile coord
Vec2 Tiled::tileCoordFromPosition(Vec2 position)
{
	int x = position.x / tileMap->getTileSize().width;
	int y = ((tileMap->getMapSize().height * tileMap->getTileSize().height) - position.y) / tileMap->getTileSize().height;

	return Vec2(x, y);
}
// ����λ��
void Tiled::setPlayerPosition(Vec2 position)
{
	Vec2 tileCoord = this->tileCoordFromPosition(position);

	if (tileCoord.x < 0 || tileCoord.y < 0 || tileCoord.x >= tileMap->getMapSize().width || tileCoord.y >= tileMap->getMapSize().height){
		return;
	}
	int tileGid = collidable->getTileGIDAt(tileCoord);
	if (tileGid > 0){ // > 0 ��Ч
		// CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
		return;
		//Value properties = tileMap->getPropertiesForGID(tileGid);
		//ValueMap propertiesMap = properties.asValueMap();
		//std::string collisionFlag = propertiesMap["Collidable"].asString();
		//if (collisionFlag == "true"){ // �ϰ�
		//	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
		//	return;
		//}
	}
	// ���þ���λ��
	player->setPosition(position);

	// �����ӵ�
	this->setViewPointCenter(player->getPosition());
}
void Tiled::setViewPointCenter(Vec2 position)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);

	x = MIN(x, (tileMap->getMapSize().width * tileMap->getTileSize().width) - visibleSize.width / 2);
	y = MIN(y, (tileMap->getMapSize().height * tileMap->getTileSize().height) - visibleSize.height / 2);

	// ��Ļ���ĵ�
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);

	Vec2 pointB = Vec2(x, y);

	Vec2 offset = pointA - pointB;

	this->setPosition(offset);
	// test
	test();
}
void Tiled::test()
{
	
}