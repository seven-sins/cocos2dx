#include "SettingScene.h"

USING_NS_CC;

Scene* SettingScene::createScene()
{
	Scene* scene = Scene::create();
	SettingScene* layer = SettingScene::create();
	scene->addChild(layer);

	return scene;
}
bool SettingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *bg = Sprite::create("setting-back.png");

	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->addChild(bg);
	//ÒôÐ§
	auto soundOnMenuItem = MenuItemImage::create(
		"on.png",
		"on.png");
	auto soundOffMenuItem = MenuItemImage::create(
		"off.png",
		"off.png");

	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingScene::menuSoundToggleCallback, this),
		soundOnMenuItem,
		soundOffMenuItem,
		NULL);
	soundToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(377, 111)));

	//ÒôÀÖ
	auto musicOnMenuItem = MenuItemImage::create(
		"on.png",
		"on.png");
	auto musicOffMenuItem = MenuItemImage::create(
		"off.png",
		"off.png");
	auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingScene::menuMusicToggleCallback, this),
		musicOnMenuItem,
		musicOffMenuItem,
		NULL);
	musicToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(377, 183)));

	//Ok°´Å¥
	auto okMenuItem = MenuItemImage::create(
		"ok-down.png",
		"ok-up.png",
		CC_CALLBACK_1(SettingScene::menuOkCallback, this));

	okMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(288, 258)));

	Menu* mn = Menu::create(soundToggleMenuItem, musicToggleMenuItem, okMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);

	return true;
}

void SettingScene::menuOkCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}

void SettingScene::menuSoundToggleCallback(Ref* pSender)
{

}

void SettingScene::menuMusicToggleCallback(Ref* pSender)
{

}