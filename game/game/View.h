#ifndef View_h
#define View_h
#include <SFML\Graphics.hpp>
using namespace sf;
sf::View view;
View getplayercoor(float x, float y)
{ 
float tempX=x; float tempY=y;
	if (x<320) tempX=320;
	if (y<275) tempY=275;
	if (y>365) tempY=365;
	if (x>450) tempX=450;
	view.setCenter(tempX,tempY);
	return view;
}
#endif