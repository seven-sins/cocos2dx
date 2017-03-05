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
	// 加载地图
	tileMap = TMXTiledMap::create("map/snow.tmx");
	this->addChild(tileMap, 0, 100);
	// 获取对象组
	TMXObjectGroup* group = tileMap->getObjectGroup("object");
	ValueMap spPoint = group->getObject("zhaoyun");
	float x = spPoint["x"].asFloat();
	float y = spPoint["y"].asFloat();
	// 添加精灵
	player = Sprite::create("zhaoyun.png");
	float spriteWidth = Base::getInstance()->getSpriteWidth(); // 精灵宽度
	float spriteHeight = Base::getInstance()->getSpriteHeight(); // 精灵高度
	float tileWidth = tileMap->getTileSize().width; // tile size
	player->setContentSize(Size(spriteWidth, spriteHeight)); // 设置精灵大小
	player->setPosition(Vec2(x + tileWidth / 2, y + tileWidth / 2));
	this->addChild(player, 2, 200);
	this->setViewPointCenter(player->getPosition());
	// 获取碰撞层
	collidable = tileMap->getLayer("collision");
	collidable->setVisible(false);
	// 添加事件响应
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
	// 获得openGL坐标
	Vec2 tochLocation = touch->getLocation();
	// 转换为模型坐标
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
// 从当前像素坐标获得tile coord
Vec2 Tiled::tileCoordFromPosition(Vec2 position)
{
	int x = position.x / tileMap->getTileSize().width;
	int y = ((tileMap->getMapSize().height * tileMap->getTileSize().height) - position.y) / tileMap->getTileSize().height;

	return Vec2(x, y);
}
// 精灵位置
void Tiled::setPlayerPosition(Vec2 position)
{
	Vec2 tileCoord = this->tileCoordFromPosition(position);

	if (tileCoord.x < 0 || tileCoord.y < 0 || tileCoord.x >= tileMap->getMapSize().width || tileCoord.y >= tileMap->getMapSize().height){
		return;
	}
	int tileGid = collidable->getTileGIDAt(tileCoord);
	if (tileGid > 0){ // > 0 有效
		// CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
		return;
		//Value properties = tileMap->getPropertiesForGID(tileGid);
		//ValueMap propertiesMap = properties.asValueMap();
		//std::string collisionFlag = propertiesMap["Collidable"].asString();
		//if (collisionFlag == "true"){ // 障碍
		//	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
		//	return;
		//}
	}
	// 设置精灵位置
	player->setPosition(position);

	// 设置视点
	this->setViewPointCenter(player->getPosition());
}
void Tiled::setViewPointCenter(Vec2 position)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);

	x = MIN(x, (tileMap->getMapSize().width * tileMap->getTileSize().width) - visibleSize.width / 2);
	y = MIN(y, (tileMap->getMapSize().height * tileMap->getTileSize().height) - visibleSize.height / 2);

	// 屏幕中心点
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