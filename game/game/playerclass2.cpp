#include "stdafx.h"
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Player.h"
#include "map.h"
#include <iostream>
#include "global.h"

//playerclass2.cpp
using namespace std;
using namespace sf;


Player::Player(Image &image, float X, float Y, int W, int H, std::string Name): Entity(image,X,Y,W,H,Name)
{ 
	
	MaxObj=0;
	state=stay;
	if (name=="Player1"){
	sprite.setTextureRect(IntRect(33, 0, w, h)); //Прямоугольник для спрайта
	/*
	File = F; //имя файла
	w = W; h = H; //высота и ширина спрайта
	dir=DIR; speed=SPEED;
	health = 100;
	MaxObj=0;
	x=50;
	y=50;
		//инициализировали переменную жизни в конструкторе
	life = true;//инициализировали логическую переменную жизни
	image.loadFromFile("images/" + File);//загружаем изображение
    image.createMaskFromColor(Color(255, 255, 255));// убераем белый фон
	texture.loadFromImage(image); // загружаем изображение в текстуру
	sprite.setTexture(texture); //заливаем спрайт текстурой
	sprite.setTextureRect(IntRect(33, 0, w, h)); //Прямоугольник для спрайта
	*/
}
}
void Player::control()
{
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				state = left;
				speed = 0.08;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				state = right;
				speed = 0.08;
			}

			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				state = up;
				speed = 0.08;
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				state = down;
				speed = 0.08;
			}
		}
void Player::update(float time) //функция бновления объекта класса. Принимает в себя float time -
	//время SFML, вследствие чего работает бесконечно, давая персонажу движение.
{
	if (life) {//проверяем, жив ли герой
		control();//функция управления персонажем
		switch (state)//тут делаются различные действия в зависимости от состояния
		{
		case right:{
			dx=speed;
			dy=0;
			CurrentFrame += 0.005*time;// переменная отвечает за то сколько времени должно пройти, чтобы перейти на следующий кадр
			
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 66, 32, 32)); 			
			//getplayercoor(GetPlayerCoordinateX(),GetPlayerCoordinateY());
			break;
			}
         case left:{//состояние идти влево
			dx = -speed;
			dy=0;
			CurrentFrame += 0.005*time;// переменная отвечает за то сколько времени должно пройти, чтобы перейти на следующий кадр

			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 99, 32, 32)); // перемещееие по кадрам влево
			//getplayercoor(GetPlayerCoordinateX(),GetPlayerCoordinateY());
			break;
			}
		case up:{//идти вверх
			dx = 0;
			dy = -speed;
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 0, 32, 32));			
			//getplayercoor(GetPlayerCoordinateX(),GetPlayerCoordinateY());
			break;
			}
		case down:{//идти вниз
			dx = 0;
			dy = speed;
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 33, 32, 32)); 				
			//getplayercoor(GetPlayerCoordinateX(),GetPlayerCoordinateY());
			break;
			}

		
		case stay:
			 {//стоим
				 
			dy = speed;
			dx = speed;
			break;
			}

		}

        x += dx*time; //движение по “X”
		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х

		y += dy*time; //движение по “Y”
		checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
		
		
		speed = 0;    //обнуляем скорость, чтобы персонаж остановился.
		
		//состояние - стоит
		
		sprite.setPosition(x, y); //переставляем спрайт в новую позицию (x, y).

		if (health <= 0){ life = false; }//если жизней меньше 0, либо равно 0, то умираем 
		}
	}

 float Player::GetPlayerCoordinateX()
 {
	 return x;
 }
  float Player::GetPlayerCoordinateY()
 {
	 return y;
 }
void Player::interactionWithMap()
{
	for (int i = y / 32; i < (y + h) / 32; i++)
		for (int j = x / 32; j<(x + w) / 32; j++){
			if (TileMap[i][j] == '0')//если наш квадратик соответствует символу “0”
					//(стена), то проверяем "направление скорости" персонажа:
		{
			if (dy>0) {//если мы шли вниз,
			y = i * 32 - h;//то стопорим (-h) координату “y” персонажа. 
				//сначала получаем координату “i” нашего квадратика на карте и 
				//затем вычитаем из высоты спрайта персонажа.
			}
			if (dy<0){
			y = i * 32 + 32;//аналогично с движением вверх.	
			}
			if (dx>0){
			x = j * 32 - w;//если идем вправо, то координата “x” равна 
							//стена (символ 0) минус ширина персонажа
			}
			if (dx < 0){
			x = j * 32 + 32; //аналогично идем влево
			}
		}	
			if (TileMap[i][j] == 's') { //если символ равен 's' (камень)
				health -= 40;
				MaxObj-= 1;
				TileMap[i][j] = ' ';//убираем камень
			}
	}

}

void Player::checkCollisionWithMap(float Dx, float Dy)	{
for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
	for (int j = x / 32; j<(x + w) / 32; j++)
	{
		if (TileMap[i][j] == '0')//если элемент тайлик земли
		{
		if (Dy > 0) { y = i * 32 - h;  dy = 0; }//по Y 
		if (Dy < 0) { y = i * 32 + 32; dy = 0; }//столкновение с верхними краями карты
		if (Dx > 0) { x = j * 32 - w; dx = 0; }//с правым краем карты
		if (Dx < 0) { x = j * 32 + 32; dx = 0; }// с левым краем карты
		}	
		if (TileMap[i][j] == 's') {
			health -= 40; //если взяли камень, переменная playerScore=playerScore+1;
			TileMap[i][j] = ' ';
		}
		
	}
};




