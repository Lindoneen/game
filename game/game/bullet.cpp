#include "stdafx.h"
#include "map.h"
#include "global.h"
#include "bullet.h"
#include "Entity.h"
#include "global.h"

using namespace std;
using namespace sf;


Bullet::Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir,float speed) :Entity(image, X, Y, W, H, Name){
		x = X; //координаты пули на карте игры
		y = Y;
		direction = dir; //направление полета пули
		SPEED = speed;
		w = h = 16; //размеры изображения пули
		life = true; //пуля жива
		sprite.setTextureRect(IntRect(272, 8, w, h));
	}


	void Bullet::update(float time)
	{
		switch (direction)
		{
		case 0: dx = -SPEED; dy = 0;   break;// state = left
		case 1: dx = SPEED; dy = 0;   break;// state = right
		case 2: dx = 0; dy = -SPEED;   break;// state = up
		case 3: dx = 0; dy = SPEED;   break;// state = down
		case 4: dx= speed; dy=0; break;
		
		}

		if (life==true){ // если пуля жива
			x += dx*time;//само движение пули по х
			y += dy*time;//по у

			if (x <= 0) x = 20;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки (сервер может тормозить!)
		if (y <= 0) y = 20;

		if (x >= 920) x = 910;// задержка пули в правой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки (сервер может тормозить!)
		if (y >= 760) y = 740;

			for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
				for (int j = x / 32; j < (x + w) / 32; j++)
				{
					if (TileMap[i][j] == '0')//если элемент наш тайлик земли, то
						life = false;// то пуля умирает
				}
			sprite.setPosition(x + w / 2, y + h / 2); //задается позицию пули
		}
	}
