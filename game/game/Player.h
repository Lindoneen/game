//Player.h
#ifndef Player_h
#define Player_h

using namespace sf;
class Player { // класс Игрока
private: 
float x, y;
public:
float w, h, dx, dy, speed; //координаты игрока х и у, высота и ширина спрайта
								//ускорение и скорость
    int MaxObj;
	int dir, health; 
	bool life;
	std::string File; //имя файла
	Image image;//сфмл изображение
    Texture expl;
	Sprite s_expl;
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт
	Player(std::string F, float W, float H, int DIR, float SPEED);
	void update(float time);
	void interactionWithMap();
	float GetPlayerCoordinateX();
	float GetPlayerCoordinateY();
	
};
#endif