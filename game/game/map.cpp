#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include "map.h"
std::string TileMap[HEIGHT_MAP] = {
	"000000000000000000000000000000",
	"0   0               0        0",
	"0                            0",
	"00                     000   0",
	"0       00000                0",
	"0     00000       0     0    0",
	"0     00         0     0    00",
	"0               0            0",
	"0         00                 0",
	"0   0              00        0",
	"0   0       0    000000      0",
	"0                            0",
	"0          000               0",
	"00         0                 0",
	"0          0     0   0000    0",
	"0       0000                 0",
	"0                            0",
	"0                            0",
	"00    0     000   0         00",
	"0            0               0",
	"0   000               0      0",
	"0      0        000          0",
	"0                            0",
	"0          0          0      0",
	"000000000000000000000000000000",

};
void randomMapGenerate()
{//рандомно расставл€ем камни

int randomElementX = 0;//переменна€ дл€ хранени€ случайного элемента по горизонтали
int randomElementY = 0;//переменна€ дл€ хранени€ случайного элемента по вертикали
srand(time(0));//»нициализаци€ генератора случайных чисел	
int countStone = 1;//количество камней

while (countStone>0){
	randomElementX = 1 + rand() % (WIDTH_MAP - 1);//псевдослучайное значение по УxФ от 1 до
		//ширина карты-1. ќграничение введено чтобы не получать числа бордюра карты
	randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//по УyФ

	if (TileMap[randomElementY][randomElementX] == ' ') {//если встретили символ пробел, 
			TileMap[randomElementY][randomElementX] = 's';  //то ставим туда камень.
			countStone--;
		}
	}
};
