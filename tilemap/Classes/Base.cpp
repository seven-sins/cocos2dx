#include "Base.h"

Base::Base()
{

}
Base::~Base()
{
	if (instance != nullptr){
		delete(instance);
		instance = nullptr;
	}
}

Base* Base::instance = new Base();

Base* Base::getInstance()
{
	if (instance){
		return instance;
	}
	else{
		return new Base();
	}
	
}
float Base::getSpriteWidth()
{
	return sprite.width;
}
float Base::getSpriteHeight()
{
	return sprite.height;
}