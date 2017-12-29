#ifndef View_h
#define View_h
#include "stdafx.h"
#include <SFML\Graphics.hpp>


using namespace sf;
sf::View view;
View getplayercoor(float x, float y)
{ 
float tempX=x; float tempY=y;
	if (x<320) tempX=320;
	if (y<350) tempY=350;
	if (y>450) tempY=450;
	if (x>640) tempX=640;
	view.setCenter(tempX,tempY);
	return view;
}
#endif