#include <SFML/Graphics.hpp>
#include "player.h"

//playerclass2.cpp

using namespace sf;


Player::Player(std::string F, float X, float Y, float W, float H, int DIR, float SPEED)
{ 
	File = F; //имя файла
	w = W; h = H; //высота и ширина спрайта
	dir=DIR; speed=SPEED;
	image.loadFromFile("images/" + File);//загружаем изображение
    image.createMaskFromColor(Color(255, 255, 255));// убераем белый фон
	texture.loadFromImage(image); // загружаем изображение в текстуру
	sprite.setTexture(texture); //заливаем спрайт текстурой
	x = X; y = Y; // начальные координаты
	sprite.setTextureRect(IntRect(33, 0, w, h)); //Прямоугольник для спрайта
}


void Player::update(float time) //функция бновления объекта класса. Принимает в себя float time -
	//время SFML, вследствие чего работает бесконечно, давая персонажу движение.
{
	switch (dir)//Даем скорость по X Y в зависимости от направления
	{
	case 0: dx = speed; dy = 0; break; //скорость по X вправо
	case 1: dx = -speed; dy = 0; break;//по X влево
	case 2: dx = 0; dy = speed; break;//по Y вниз
	case 3: dx = 0; dy = -speed; break;//по Y вверх
	}

	x += dx*time; //движение по X
	y += dy*time; //движение по Y
	speed = 0;    //обнуляем скорость, чтобы персонаж остановился.
	sprite.setPosition(x, y); //выводим спрайт в позицию (x, y). 
			
}
   