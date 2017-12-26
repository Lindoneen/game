#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <list>
#include "map.h"
#include "global.h"
#include "Camera.h"





//playerclass2.cpp
using namespace std;
using namespace sf;
////////////////////////////КЛАСС СУЩНОСТЬ////////////////////////
class Entity {
public:
	enum { left, right, up, down, stay} state;// тип перечисления - состояние объекта
	float dx, dy, x, y, speed, moveTimer;//добавили переменную таймер для будущих целей
	int w, h, health; //переменная “health”, хранящая жизни игрока
	bool life; //переменная “life” жизнь, логическая
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт 
	float CurrentFrame;//хранит текущий кадр
	std::string name;//враги могут быть разные, врагов можно различать по именам
	//каждому можно дать свое действие в update() в зависимости от имени

	Entity(Image &image, float X, float Y, int W, int H, std::string Name){
		x = X; y = Y; //координата появления спрайта
		w = W; h = H; 
		name = Name; 
		moveTimer = 0;
		dx = 0; dy = 0; 
		speed = 0; 
		CurrentFrame = 0;
		health = 100;
		life = true; //инициализировали логическую переменную жизни, герой жив
		texture.loadFromImage(image); //заносим наше изображение в текстуру
		sprite.setTexture(texture); //заливаем спрайт текстурой
	}

FloatRect getRect(){//метод получения прямоугольника. его коорд, размеры (шир,высот).
	FloatRect FR(x, y, w, h); // переменная FR типа FloatRect
	return FR;
	//return FloatRect(x, y, w, h);
	//Тип данных (класс) "sf::FloatRect" позволяет хранить четыре координаты прямоугольника
		//в нашей игре это координаты текущего расположения тайла на карте
		//далее это позволит спросить, есть ли ещё какой-либо тайл на этом месте 
		//эта ф-ция нужна для проверки пересечений 
	}
	virtual void update(float time) = 0;
};

class Player: public Entity{ // класс Игрока


public:
	 int playerScore;
    int MaxObj;
 
	




Player(Image &image,float X, float Y, float W, float H,std::string Name) : Entity(image,X,Y,W,H,Name)
{ 
	playerScore=0;
	MaxObj=0;
	state=stay;
	if (name=="Player1"){
 

	sprite.setTextureRect(IntRect(33, 0, w, h)); //Прямоугольник для спрайта

	
}
}
void control()
{
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				state = left;
				speed = 0.1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				state = right;
				speed = 0.1;
			}

			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				state = up;
				speed = 0.1;
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				state = down;
				speed = 0.1;
			}
		}

void checkCollisionWithMap(float Dx, float Dy)	{
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
}


void update(float time) //функция бновления объекта класса. Принимает в себя float time -
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
			getPlayerCamera(GetPlayerCoordinateX(),GetPlayerCoordinateY());
			break;
			}
         case left:{//состояние идти влево
			dx = -speed;
			dy=0;
		CurrentFrame += 0.005*time;
		// переменная отвечает за то сколько времени должно пройти, чтобы перейти на следующий кадр

			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 99, 32, 32)); // перемещееие по кадрам влево
			getPlayerCamera(GetPlayerCoordinateX(),GetPlayerCoordinateY());
			break;
			}
		case up:{//идти вверх
			dx = 0;
			dy = -speed;
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 0, 32, 32));			
			 getPlayerCamera(GetPlayerCoordinateX(),GetPlayerCoordinateY());
			break;
			}
		case down:{//идти вниз
			dx = 0;
			dy = speed;
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 33, 32, 32)); 				
			getPlayerCamera(GetPlayerCoordinateX(),GetPlayerCoordinateY());
			break;
			}
				  if (speed=0) state=stay;
		case stay:{//стоим
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
		state = stay; //состояние - стоит

		sprite.setPosition(x, y); //переставляем спрайт в новую позицию (x, y).

		if (health <= 0){ life = false; }//если жизней меньше 0, либо равно 0, то умираем 
		}
	}

 float GetPlayerCoordinateX()
 {
	 return x;
 }
  float GetPlayerCoordinateY()
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
			if (TileMap[i][j] == 's') 
			{ //если символ равен 's' (камень)
				health -= 40;
				MaxObj-=1;
				TileMap[i][j] = ' ';//убираем камень
			}
	}
		

}

};

class Enemy :public Entity{
public:
	int direction;//направление движения врага
Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name){
	if (name == "EasyEnemy"){
		//Задаем спрайту один прямоугольник для
		//вывода одного игрока. IntRect – для приведения типов
		sprite.setTextureRect(IntRect(332, 135, w, h));
		direction = rand() % (3); //Направление движения врага задаём случайным образом
			//через генератор случайных чисел
			speed = 0.1;//даем скорость.этот объект всегда двигается
			dx = speed;
		}
	}

void checkCollisionWithMap(float Dx, float Dy)//ф-ция проверки столкновений с картой
	{
	for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
		if (TileMap[i][j] == '0')//если элемент - тайлик земли
			{
			if (Dy > 0) { y = i * 32 - h;  dy = -0.1; 
					direction = rand() % (3); //Направление движения врага
						}//по Y 
			if (Dy < 0) { y = i * 32 + 32; dy = 0.1;  
					direction = rand() % (3);//Направление движения врага 
						}//столкновение с верхними краями 
			if (Dx > 0) { x = j * 32 - w; dx = -0.1;  
					direction = rand() % (3);//Направление движения врага 
						}//с правым краем карты
					if (Dx < 0) { x = j * 32 + 32; dx = 0.1;  
					direction = rand() % (3); //Направление движения врага
						}// с левым краем карты
				}
			}
	}

	void update(float time)
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
			sprite.setTextureRect(IntRect((330+33 * int(CurrentFrame)), 201, 32, 32)); 			
			
			break;
			}
         case left:{//состояние идти влево
			dx = -speed;
			dy=0;
		CurrentFrame += 0.005*time;
		// переменная отвечает за то сколько времени должно пройти, чтобы перейти на следующий кадр

			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((330+33 * int(CurrentFrame)), 234, 32, 32)); // перемещееие по кадрам влево
			
			break;
			}
		case up:{//идти вверх
			dx = 0;
			dy = -speed;
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((330+33 * int(CurrentFrame)), 134, 32, 32));			
			
			break;
			}
		case down:{//идти вниз
			dx = 0;
			dy = speed;
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((330+33 * int(CurrentFrame)), 167 , 32, 32)); 				
			
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
		}
	};
//класс Enemy закрыт

  int main()
{
	//Создаём окно
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();// получаем режим отображения
	sf::RenderWindow window(sf::VideoMode(640, 550, desktop.bitsPerPixel), "TANKZZZ");// устанавливаем размер окна и режим отображения
	camera.reset(sf::FloatRect(0,0,640,550));
	Font font;//шрифт 
	Font death_font;
	death_font.loadFromFile("CHILLER.ttf");
    font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
Text text("", font, 20);//создаем объект текст. размер шрифта(в пикселях);
//сам объект текст (не строка)
text.setColor(Color::Red);//покрасили текст в красный.
text.setStyle(Text::Bold);//жирный текст.

Text death_text("", death_font, 40);
death_text.setColor(Color::Black);
death_text.setStyle(Text::Bold);


	Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/tank.png");//загружаем файл для карты

	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

	Image expl_image;
	expl_image.loadFromFile("images/tank.png" );//загружаем изображение

    expl_image.createMaskFromColor(Color(0, 0, 0));// убераем белый фон

	Texture expl;
	expl.loadFromImage(expl_image); // загружаем изображение в текстуру

	Sprite s_expl;
	s_expl.setTexture(expl);
	


	float CurrentExplFrame= 0;
	float CurrentFrame = 0;//хранит текущий кадр
	Clock clock;
	Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры 
	int gameTime = 0;
	Image heroImage;
	
	heroImage.loadFromFile("images/hero.png");
	heroImage.createMaskFromColor(Color(255, 255, 255));
	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/Tank.png");
	easyEnemyImage.createMaskFromColor(Color(0, 0, 0));
	Player p(heroImage,50,50, 32.0, 32.0,"Player1");
	
	std::list<Entity*>  enemies; //список врагов
	std::list<Entity*>::iterator it; //итератор чтобы проходить по элементам списка
	const int ENEMY_COUNT = 3;	//максимальное количество врагов в игре
    
	int enemiesCount = 0;	//текущее количество врагов в игре
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
	float xr = 150 + rand() % 500; //случайная координата врага на поле игры по оси “x”
	float yr = 150 + rand() % 350; //случайная координата врага на поле игры по оси “y”
		//создаем врагов и помещаем в список
		enemies.push_back(new Enemy(easyEnemyImage, xr, yr, 32, 32, "EasyEnemy"));
		enemiesCount += 1; //увеличили счётчик врагов
	}


	int createObjectForMapTimer = 0;
	int ret = 0;
	while (window.isOpen())// пока окно открыто делай
	{
		
		float time = clock.getElapsedTime().asMicroseconds();// взять время в микросекундах
		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();
		clock.restart();// перезапуск счетчика
		time = time / 800;// устанавливаем скорость игры
		
		createObjectForMapTimer += time;//наращиваем таймер
		if (createObjectForMapTimer>400){
			
			if (p.MaxObj<3)
			{
				p.MaxObj+=1;
			    ret=p.MaxObj;
			randomMapGenerate();//генерация  камней
	        createObjectForMapTimer = 0;//обнуляем таймер
			}
			else {
				createObjectForMapTimer = 0;
			}
			cout << ret;
		}
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)// если на окно нажать закрыть цикл прекратиться
				window.close();
		} // всё

		
		
		
		    p.update(time);
			
		//оживляем врагов
		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			(*it)->update(time); //запускаем метод update()
		}



			cameramap(time);
			window.setView(camera);

			//Проверка пересечения игрока с врагами
//Если пересечение произошло, то "health = 0", игрок обездвижевается и 
//выводится сообщение "you are lose"

if (p.life == true){//если игрок жив
	for (it = enemies.begin(); it != enemies.end(); it++){//бежим по списку врагов
		if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "EasyEnemy"))
				{
					p.health = 0;
					std::cout << "you are lose";
				}
			}
		}
			window.clear();// чистим окно
		                 

		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
		if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(133, 100, 32, 32)); //если
				//встретили символ пробел, то рисуем 1-й квадратик
		if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(300, 0, 32, 32));//если
				//встретили символ s, то рисуем 2й квадратик
		if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(0, 102, 32, 32));//если
				//встретили символ 0, то рисуем 3й квадратик
		if ((TileMap[i][j] == 't')) s_map.setTextureRect(IntRect(299, 101, 30, 30));//если
				//встретили символ 0, то рисуем 3й квадратик
			s_map.setPosition(j * 32, i * 32);//раскладываем квадратики в карту.

			
			

			window.draw(s_map);//рисуем квадратики на экран
			
			}

		
	std::ostringstream playerHealthString, gameTimeString;//объявили переменную здоровья и времени
playerHealthString << p.health; gameTimeString << gameTime;//формируем строку
text.setString("Здоровье: " + playerHealthString.str() + "\nВремя игры: " + gameTimeString.str());//задаем строку тексту
text.setPosition(camera.getCenter().x-200, camera.getCenter().y-250);//задаем позицию текста
window.draw(text);//рисуем этот текст
if (p.life==true) 
		
		{  
		window.draw(p.sprite);//рисуем спрайт
		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			window.draw((*it)->sprite); //рисуем enemies объекты
		}

		window.display();// выводим на экран

       }
		else 
		
		{    
		
			CurrentExplFrame += 0.001*time;// переменная отвечает за то сколько времени должно пройти, чтобы перейти на следующий кадр

			if (CurrentExplFrame > 3) CurrentExplFrame -= 3; 
			s_expl.setTextureRect(IntRect((1+33 * int(CurrentExplFrame)), 1, 32, 32)); // перемещееие по кадрам влево
			s_expl.setPosition(p.GetPlayerCoordinateX(), p.GetPlayerCoordinateY());
			death_text.setString("LOL YOU DIED LOL LOL YOU DIED ");//задаем строку тексту
        death_text.setPosition(camera.getCenter().x-180, camera.getCenter().y-100);//задаем позицию текста
        window.draw(death_text);//рисуем этот текст
		
			window.draw(p.sprite);
			window.draw(s_expl);
			window.display();
			 
		
		}
	}
window.clear();
	return 0;
	}
	
