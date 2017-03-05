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
	// ����size
	struct SPRITE{
		float width = 48; float height = 64;
	}sprite;
};

