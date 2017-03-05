#pragma once
using namespace std;

class Base
{
public:
	static Base* getInstance();
	float getSpriteWidth();
	float getSpriteHeight();
private:
	Base();
	virtual ~Base();
	static Base* instance;
	// ¾«Áésize
	struct SPRITE{
		float width = 32; float height = 32;
	}sprite;
};

