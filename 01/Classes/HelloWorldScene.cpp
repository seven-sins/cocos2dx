#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("background.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg); 

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hero.plist");
	// 开始菜单精灵
	auto startUp = Sprite::createWithSpriteFrameName("start-up.png");
	auto startDown = Sprite::createWithSpriteFrameName("start-down.png");
	// 开始菜单
	auto startMenuItem = MenuItemSprite::create(startUp, 
			startDown,
			CC_CALLBACK_1(HelloWorld::menuStartCallback, this)
	);
	startMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(260, 100)));
	
	// 设置菜单
	auto settingMenuItem = MenuItemImage::create("setting-up.png", 
		"setting-down.png",
		CC_CALLBACK_1(HelloWorld::menuSettingCallback, this));
	settingMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(158, 210)));

	// 帮助菜单
	auto helpMenuItem = MenuItemImage::create("help-up.png",
		"help-down.png",
		CC_CALLBACK_1(HelloWorld::menuHelpCallback, this));
	helpMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(366, 210)));
	//
	auto menu = Menu::create(startMenuItem, settingMenuItem, helpMenuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

    return true;
}

void HelloWorld::menuStartCallback(Ref* pSender)
{

}
void HelloWorld::menuSettingCallback(Ref* pSender)
{
	Scene* setting = SettingScene::createScene();
	auto reScene = TransitionSplitRows::create(1.0f, setting);

	// Director::getInstance()->replaceScene(setting);
	Director::getInstance()->pushScene(reScene);
}
void HelloWorld::menuHelpCallback(Ref* pSender)
{

}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
void HelloWorld::onEnter()
{
	Layer::onEnter();
	log("onEnter");
}
void HelloWorld::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("onEnterTransitionDidFinish");
}
void HelloWorld::onExit()
{
	Layer::onExit();
	log("onExit");
}
void HelloWorld::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
	log("onExitTransitionDidStart");
}
void HelloWorld::cleanup()
{
	Layer::cleanup();
	log("cleanup");
}