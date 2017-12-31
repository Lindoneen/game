#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <list>
#include "map.h"
#include "global.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "View.h"
#include "bullet.h"




//playerclass2.cpp
using namespace std;
using namespace sf;







  int main()
{
	//Создаём окно
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();// получаем режим отображения
	sf::RenderWindow window(sf::VideoMode(1400, 1000, desktop.bitsPerPixel), "TANKZZZ");// устанавливаем размер окна и режим отображения
//	camera.reset(sf::FloatRect(0,0,640,550));
	view.reset(sf::FloatRect(0, 0, 640, 700));
	Font font;//шрифт 
	Font death_font;
	death_font.loadFromFile("CHILLER.ttf");
    font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
Text text("", font, 20);//создаем объект текст. размер шрифта(в пикселях);
//сам объект текст (не строка)
text.setColor(Color::Red);//покрасили текст в красный.
text.setStyle(Text::Bold);//жирный текст.

Text death_text("", death_font, 80);
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

    expl_image.createMaskFromColor(Color(255, 255, 255));// убераем белый фон

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
	int bulletSpawnTimer=0;
	
	heroImage.loadFromFile("images/hero.png");
	heroImage.createMaskFromColor(Color(255, 255, 255));
	Image BulletImage;//изображение для пули
    BulletImage.loadFromFile("images/tank.png");//загрузили картинку в объект изображения
	BulletImage.createMaskFromColor(Color(255, 255, 255));
	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/tank.png");
	easyEnemyImage.createMaskFromColor(Color(255, 255, 255));
	Player p(heroImage,50,50, 32.0, 32.0,"Player1");
	
	std::list<Entity*>  enemies;//список врагов
	std::list<Entity*>  Bullets;
	std::list<Entity*>::iterator it;
	
	//итератор чтобы проходить по элементам списка
	const int ENEMY_COUNT = 7;	//максимальное количество врагов в игре
    srand (time(0));
	int enemiesCount = 0;	//текущее количество врагов в игре
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		
	float xr = 100 + rand() % 400; //случайная координата врага на поле игры по оси “x”
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
		time = time / 900;// устанавливаем скорость игры
		
		createObjectForMapTimer += time;//наращиваем таймер
		if (createObjectForMapTimer>400){
			
			if (p.MaxObj<10)
			{
				p.MaxObj+=1;
			    ret=p.MaxObj;
			randomMapGenerate();//генерация  камней
	        createObjectForMapTimer = 0;//обнуляем таймер
			}
			else {
				cout<<p.MaxObj;
				createObjectForMapTimer = 0;
			}
			
		}
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)// если на окно нажать закрыть цикл прекратиться
			window.close();

		//стреляем по нажатию клавиши "P"
		if (event.type == sf::Event::KeyPressed)
		{
		if (event.key.code == sf::Keyboard::Z)
		{
		//добавляем в список Bullets пулю
			
			Bullets.push_back(new Bullet(BulletImage, p.x, p.y, 16, 16, "Bullet", p.state,0.5));
				}
			}
		}

		 // всё

		
		
		
		    p.update(time);
			
		
			for (it = enemies.begin(); it != enemies.end(); it++)
		{
			(*it)->update(time); //запускаем метод update()

		}

			if (bulletSpawnTimer<1600);
			bulletSpawnTimer++;
			if(bulletSpawnTimer>=1600)
			{
			for (it = enemies.begin(); it != enemies.end(); it++)
		{
		
	
			if((*it)->dx<0)
			{
				
			
					
	
			Bullets.push_back(new Bullet(BulletImage,(*it)->x, (*it)->y, 16, 16, "eBullet",0,0.2));
			  bulletSpawnTimer=0;
			
			

			}
			
			
				if((*it)->dx>0)
			{
	        		
	
			Bullets.push_back(new Bullet(BulletImage,(*it)->x, (*it)->y, 16, 16, "eBullet",1,0.2));
			  bulletSpawnTimer=0;
			
			
			}
			
			
			if((*it)->dy>0)
			{
	   	
	
			Bullets.push_back(new Bullet(BulletImage,(*it)->x, (*it)->y, 16, 16, "eBullet",3,0.20));
			bulletSpawnTimer=0;
			
			
			}
			if((*it)->dy<0) 
			{
	   		
	
			Bullets.push_back(new Bullet(BulletImage,(*it)->x, (*it)->y, 16, 16, "eBullet",2,0.2));
			  bulletSpawnTimer=0;
			
			
			}
			}
			}
		for (/*std::list<Entity*>::iterator*/ it = Bullets.begin(); it != Bullets.end(); it++)
		{
			(*it)->update(time); //запускаем метод update()
		}

		for (it= Bullets.begin(); it != Bullets.end(); it++)
		{
			Entity *enemy=*it;
			if ((*it)->name=="Bullet")
				if ((*it)->health>0)
				{
				for (std::list<Entity*>::iterator it2=enemies.begin(); it2!=enemies.end(); it2++)
				{
					if  ((*it)->getRect().intersects((*it2)->getRect( ) ))
					{(*it)->life=false; (*it2)->health-=25;}
				}
				}
		}
		


//			cameramap(time);
		//	window.setView(camera);

			//Проверка пересечения игрока с врагами
//Если пересечение произошло, то "health = 0", игрок обездвижевается и 
//выводится сообщение "you are lose"

if (p.life == true){//если игрок жив
	for (it = enemies.begin(); it != enemies.end(); it++){//бежим по списку врагов
		if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "EasyEnemy"))
				{
					if((*it)->dx>0){
						//eсли враг едет в право
						(*it)->x=p.x-50;//(*it)->w;
						//p.health -=5;
					}
					if((*it)->dx<0){
						(*it)->x=p.x+50;//(*it)->w;//eсли враг едет влево
						//p.health -=5;
					}
					if((*it)->dy>0){
						(*it)->y=p.y-50;//(*it)->h; //eсли враг едет вниз
						//p.health -=5;
					}
					if((*it)->dy<0){
						(*it)->y=p.y+50;	//(*it)->h; //eсли враг едет вниз
						//p.health -=5;
					}
					std::cout << p.state;
				}
			}
		
   for (std::list<Entity*>::iterator it2=Bullets.begin(); it2!=Bullets.end(); it2++)//бежим по списку пуль
	   {
		if ((p.getRect().intersects((*it2)->getRect())) && ((*it2)->name == "eBullet"))
		{
			p.health-=20;
			(*it2)->life=false;
		}

   }
}
       //Проверяем список на наличие "мертвых" пуль и удаляем их
		for (it = Bullets.begin(); it != Bullets.end(); )//говорим что проходимся от начала до конца
		{// если этот объект мертв, то удаляем его
			if ((*it)-> life == false)
			{ 
				delete *it;
				it = Bullets.erase(it); 
				
			}			
else  
	it++; //и идем курсором (итератором) к след объекту.
		}
			for (it = enemies.begin(); it != enemies.end(); )//говорим что проходимся от начала до конца
		{// если этот объект мертв, то удаляем его
			if ((*it)-> life == false)
			{ 
				delete *it;
				it = enemies.erase(it);
				enemiesCount-=1;
			}			
else  
	it++; //и идем курсором (итератором) к след объекту.
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
text.setPosition(view.getCenter().x-200, view.getCenter().y-250);//задаем позицию текста
window.draw(text);//рисуем этот текст
if (p.state!=5)
{
	getplayercoor(p.GetPlayerCoordinateX(),p.GetPlayerCoordinateY());
}
window.setView(view);
if (enemiesCount==0){
		death_text.setString("You win ");//задаем строку тексту
        death_text.setPosition(view.getCenter().x-180, view.getCenter().y-100);//задаем позицию текста
        window.draw(death_text);//рисуем этот текст
}
if (p.life==true) 
		
		{  
		window.draw(p.sprite);//рисуем спрайт
		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			if ((*it)->life)
			window.draw((*it)->sprite);//рисуем enemies объекты
		}
		
		//рисуем пули
		for (it = Bullets.begin(); it != Bullets.end(); it++)
		{
			if ((*it)->life) //если пуля жива, то рисуем её
				window.draw((*it)->sprite);
			
		}

		window.display();// выводим на экран

       }
		else
		{ 
			if (p.life==false);
		
		{    
		
			CurrentExplFrame += 0.001*time;// переменная отвечает за то сколько времени должно пройти, чтобы перейти на следующий кадр

			if (CurrentExplFrame > 3) CurrentExplFrame -= 3; 
			s_expl.setTextureRect(IntRect((1+33 * int(CurrentExplFrame)), 1, 32, 32)); // перемещееие по кадрам влево
			s_expl.setPosition(p.GetPlayerCoordinateX(), p.GetPlayerCoordinateY());
			death_text.setString("LOL YOU DIED LOL LOL YOU DIED ");//задаем строку тексту
        death_text.setPosition(view.getCenter().x-180, view.getCenter().y-100);//задаем позицию текста
        window.draw(death_text);//рисуем этот текст
		
			window.draw(p.sprite);
			window.draw(s_expl);
			window.display();
			 
		
		}

	}
}
window.clear();
	return 0;
	}
	
