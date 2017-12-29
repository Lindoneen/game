#ifndef Bullet_h
#define Bullet_h
#include <SFML\Graphics.hpp>
#include "stdafx.h"
#include "Entity.h"
using namespace std;
using namespace sf;


class Bullet :public Entity{//класс пули
public:
	float SPEED;
	int direction;
	Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir,float speed);
	~Bullet() {};
	void update(float time);
};
#endif