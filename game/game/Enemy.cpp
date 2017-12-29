#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "Enemy.h"
#include "map.h"
#include "global.h"
using namespace std;
using namespace sf;

Enemy::Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name){
	if (name == "EasyEnemy"){
		
		
		sprite.setTextureRect(IntRect(331, 135, w, h));
		
		direction = rand() % (3); //Направление движения врага задаём случайным образом
			//через генератор случайных чисел
			speed = 0.1;//даем скорость.этот объект всегда двигается
			dx = speed;
		}
	}
void Enemy::checkCollisionWithMap(float Dx, float Dy)//ф-ция проверки столкновений с картой
	{
		
	for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			
		if (TileMap[i][j] == '0')//если элемент - тайлик земли
			{
			if (Dy > 0) { y = i * 32 - h;  dy = -0.1; 
					direction = rand() % (4); //Направление движения врага
						}//по Y 
			if (Dy < 0) { y = i * 32 + 32; dy = 0.1;  
					direction = rand() % (4);//Направление движения врага 
						}//столкновение с верхними краями 
			if (Dx > 0) { x = j * 32 - w; dx = -0.1;  
					direction = rand() % (4);//Направление движения врага 
						}//с правым краем карты
					if (Dx < 0) { x = j * 32 + 32; dx = 0.1;  
					direction = rand() % (4); //Направление движения врага
						}// с левым краем карты
				}
			}
	}

	void Enemy::update(float time)
	{
		if (name == "EasyEnemy"){//для персонажа с таким именем логика будет такой

		if (life) {//проверяем, жив ли герой
		switch (direction)//делаются различные действия в зависимости от состояния
		{
		case right:{
			dx=speed;
			dy=0;
			CurrentFrame += 0.005*time;// переменная отвечает за то сколько времени должно пройти, чтобы перейти на следующий кадр
			
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((331+33 * int(CurrentFrame)), 199, 32, 32)); 			
			
			break;
			}
         case left:{//состояние идти влево
			dx = -speed;
			dy=0;
		CurrentFrame += 0.005*time;
		// переменная отвечает за то сколько времени должно пройти, чтобы перейти на следующий кадр

			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((331+33 * int(CurrentFrame)), 232, 32, 32)); // перемещееие по кадрам влево
			
			break;
			}
		case up:{//идти вверх
			dx = 0;
			dy = -speed;
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((331+33 * int(CurrentFrame)), 133, 32, 32));			
			
			break;
			}
		case down:{//идти вниз
			dx = 0;
			dy = speed;
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((331+33 * int(CurrentFrame)), 166 , 32, 32)); 				
			
			break;
			}
				  if (speed=0) state=stay;
		case stay:{//стоим
			dy = speed;
			dx = speed;
			break;
			}

		}
		}

		x += dx*time; //движение по “X”
		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х

		y += dy*time; //движение по “Y”
		checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y

		sprite.setPosition(x, y); //спрайт в позиции (x, y).

		if (health <= 0){ life = false; }//если жизней меньше 0, либо равно 0, то умираем
		}
		};
	