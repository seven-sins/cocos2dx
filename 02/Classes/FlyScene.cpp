#include "FlyScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* FlyScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = FlyScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool FlyScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// add background
	auto bg = Sprite::create("Background800x480.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);
	// add label
	Label* placeLabel = Label::createWithBMFont("fonts/fnt2.fnt", "Place");
	MenuItemLabel* placeMenu = MenuItemLabel::create(placeLabel,
		CC_CALLBACK_1(FlyScene::placeCallback, this));
	placeMenu->setTag(PLACE_TAG);

	// add label
	Label* flipXLabel = Label::createWithBMFont("fonts/fnt2.fnt", "FlipX");
	MenuItemLabel* flipXMenu = MenuItemLabel::create(flipXLabel,
		CC_CALLBACK_1(FlyScene::placeCallback, this));
	flipXMenu->setTag(FLIPX_TAG);

	// add label
	Label* flipYLabel = Label::createWithBMFont("fonts/fnt2.fnt", "FlipY");
	MenuItemLabel* flipYMenu = MenuItemLabel::create(flipYLabel,
		CC_CALLBACK_1(FlyScene::placeCallback, this));
	flipYMenu->setTag(FLIPY_TAG);

	// add label
	Label* hideLabel = Label::createWithBMFont("fonts/fnt2.fnt", "Hide & Show");
	MenuItemLabel* hideMenu = MenuItemLabel::create(hideLabel,
		CC_CALLBACK_1(FlyScene::placeCallback, this));
	hideMenu->setTag(HIDE_TAG);

	// add label
	Label* toggleLabel = Label::createWithBMFont("fonts/fnt2.fnt", "Toggle");
	MenuItemLabel* toggleMenu = MenuItemLabel::create(toggleLabel,
		CC_CALLBACK_1(FlyScene::placeCallback, this));
	toggleMenu->setTag(TOGGLE_TAG);

	Menu* menu = Menu::create(placeMenu, flipXMenu, flipYMenu, hideMenu, toggleMenu, NULL);
	menu->alignItemsVertically();
	//menu->setPosition(Vec2::ZERO);

	this->addChild(menu);

    return true;
}

void FlyScene::placeCallback(Ref* pSender)
{
	MenuItem* menuItem = (MenuItem*)pSender;
	log("tag = %d", menuItem->getTag());

	Scene* scene = Scene::create();
	ActionScene* layer = ActionScene::create();
	layer->flag = menuItem->getTag();
	scene->addChild(layer);

	// Scene* action = ActionScene::createScene();
	auto reScene = TransitionSlideInL::create(1.0f, scene);

	Director::getInstance()->pushScene(reScene);
}