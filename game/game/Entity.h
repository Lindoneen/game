//Entity.h
#ifndef Entity_h
#define Entity_h
#include "stdafx.h"
#include <SFML/Graphics.hpp>
using namespace sf;
class Entity {
public:
	enum { left, right, up, down, stay} state;// тип перечислени€ - состо€ние объекта
	float dx, dy, x, y, speed;//добавили переменную таймер дл€ будущих целей
	int w, h, health; //переменна€ УhealthФ, хран€ща€ жизни игрока
	bool life; //переменна€ УlifeФ жизнь, логическа€
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт 
	float CurrentFrame;//хранит текущий кадр
	std::string name;//враги могут быть разные, врагов можно различать по именам
	//каждому можно дать свое действие в update() в зависимости от имени
	virtual void update(float time)=0;
	Entity(Image &image, float X, float Y, int W, int H, std::string Name);//  онструктор Entity
	virtual ~Entity(){ //¬иртуальный деструктор
	};
	FloatRect getRect(); //ѕолучить координаты тайла по х и у
};
#endif