#include "ActionScene.h"
#include "FlyScene.h"

USING_NS_CC;

Scene* ActionScene::createScene()
{
	Scene* scene = Scene::create();
	ActionScene* layer = ActionScene::create();
	scene->addChild(layer);

	return scene;
}
bool ActionScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// add background
	Sprite* bg = Sprite::create("Background800x480.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);

	this->planSprite = Sprite::create("Plane.png");
	this->planSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(this->planSprite);

	// add menu
	MenuItemImage* goMenuItem = MenuItemImage::create("Go-up.png", "Go-down.png",
		CC_CALLBACK_1(ActionScene::goCallback, this)
		);
	goMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2, 77));

	MenuItemImage* backMenuItem = MenuItemImage::create("Back-up.png", "Back-down.png",
		CC_CALLBACK_1(ActionScene::backCallback, this)
		);
	backMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2, 22));

	Menu* menu = Menu::create(goMenuItem, backMenuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	hidden = false;

	return true;
}

void ActionScene::goCallback(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 p = Vec2(CCRANDOM_0_1() * visibleSize.width, CCRANDOM_0_1() * visibleSize.height);

	switch (this->flag)
	{
	case PLACE_TAG:
		this->planSprite->runAction(Place::create(p));
		break;
	case FLIPX_TAG:
		this->planSprite->runAction(FlipX::create(true));
		break;
	case FLIPY_TAG:
		this->planSprite->runAction(FlipY::create(true));
		break;
	case HIDE_TAG:
		if (this->hidden){
			this->planSprite->runAction(Hide::create());
		}
		else{
			this->planSprite->runAction(Show::create());
		}
		
		break;
	case TOGGLE_TAG:
		this->planSprite->runAction(ToggleVisibility::create());
		break;
	default:
		break;
	}
}

void ActionScene::backCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}

void ActionScene::onEnter()
{
	Layer::onEnter();
	log("this tag = %d", this->flag);
}