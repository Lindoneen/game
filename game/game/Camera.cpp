#include <sfml/Graphics.hpp>
#include "Camera.h"
using namespace sf;

View getPlayerCamera(float x, float y)
{
	float tempX=x; float tempY=y;
	if (x<320) tempX=320;
	if (y<275) tempY=275;
	if (y>365) tempY=365;
	if (x>450) tempX=450;
	camera.setCenter(tempX,tempY);
	return camera;
}

View cameramap(float time)
{
	if (Keyboard::isKeyPressed(Keyboard::J))
	{ camera.move(0.1*time, 0); }
	if (Keyboard::isKeyPressed(Keyboard::L))
	{ camera.move(-0.1*time, 0); }
	if (Keyboard::isKeyPressed(Keyboard::I))
	{ camera.move(0, -0.1*time); }
	if (Keyboard::isKeyPressed(Keyboard::K))
	{ camera.move(0, 0.1*time); }
	return camera;
};