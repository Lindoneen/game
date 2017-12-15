//Player.h
#ifndef Player_h
#define Player_h

using namespace sf;
class Player { // класс Игрока
public:
float x, y, w, h, dx, dy, speed; //координаты игрока х и у, высота и ширина спрайта 
								//ускорение и скорость
	int dir, health; 
	bool life;
	std::string File; //имя файла
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт
	Player(std::string F, float X, float Y, float W, float H, int DIR, float SPEED);
	void update(float time);
	void interactionWithMap();

	
};
#endif