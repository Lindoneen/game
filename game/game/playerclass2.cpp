#include <SFML/Graphics.hpp>
#include "player.h"
#include "map.h"
#include "global.h"

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
	interactionWithMap();	
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
				x = 300; y = 300;//какое-то действие...телепортация героя
				TileMap[i][j] = ' ';//убираем камень
			}
	}

};



