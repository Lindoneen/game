#ifndef Camera_h
#define Camera_h
#include <sfml/Graphics.hpp>
using namespace sf;

 View camera;
View getPlayerCamera(float x, float y);

View cameramap(float time);

#endif