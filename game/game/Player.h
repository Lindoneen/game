//Player.h
#ifndef Player_h
#define Player_h
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Entity.h"


using namespace sf;
using namespace std;
class Player:public Entity  { // класс Игрока

public:
    int MaxObj;	
	Player(Image &image, float X, float Y, int W, int H, std::string Name);
	~Player(){};
	void update(float time);
	void interactionWithMap();
	float GetPlayerCoordinateX();
	float GetPlayerCoordinateY();
	void control();
	void checkCollisionWithMap(float Dx, float Dy);

	
};
#endif