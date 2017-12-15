#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "player.h"// подключаем заголовок с классом
#include "map.h"
#include "global.h"


  int main()
{
	//Создаём окно
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();// получаем режим отображения
	sf::RenderWindow window(sf::VideoMode(640, 550, desktop.bitsPerPixel), "TANKZZZ");// устанавливаем размер окна и режим отображения
	
	Font font;//шрифт 
font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
Text text("", font, 20);//создаем объект текст. размер шрифта(в пикселях);
//сам объект текст (не строка)
text.setColor(Color::Red);//покрасили текст в красный.
text.setStyle(Text::Bold);//жирный текст.

	Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/tank.png");//загружаем файл для карты

	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом
	
	float CurrentFrame = 0;//хранит текущий кадр
	Clock clock;
	Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры 
	int gameTime = 0;

	Player p("hero.png", 250, 250, 32.0, 32.0, 0, 0.0);// Начальные координаты

	while (window.isOpen())// пока окно открыто делай
	{
		float time = clock.getElapsedTime().asMicroseconds();// взять время в микросекундах
		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();
		clock.restart();// перезапуск счетчика
		time = time / 800;// устанавливаем скорость игры

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)// если на окно нажать закрыть цикл прекратиться
				window.close();
		} // всё

		if (p.life) {
		//движение по нажатию клавиш
	if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
		p.dir = 1; p.speed = 0.1;
 	

		CurrentFrame += 0.005*time;// переменная отвечает за то сколько времени должно пройти, чтобы перейти на следующий кадр

			if (CurrentFrame > 8) CurrentFrame -= 8; 
			p.sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 99, 32, 32)); // перемещееие по кадрам влево
			
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || 
	 	 	 	 	 	 	 (Keyboard::isKeyPressed(Keyboard::D)))) {	
								 p.dir = 0; p.speed = 0.1;//направление вправо
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			p.sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 66, 32, 32)); 			

	

		}

		if ((Keyboard::isKeyPressed(Keyboard::Up) || 
	 	 	 	 	 	 	 (Keyboard::isKeyPressed(Keyboard::W)))) {
								 p.dir = 3; p.speed = 0.1;//направление вверх
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			p.sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 0, 32, 32));			
			 
		}

		if ((Keyboard::isKeyPressed(Keyboard::Down) || 
	 	 	 	 	 	 	 (Keyboard::isKeyPressed(Keyboard::S)))) {
								 p.dir = 2; p.speed = 0.1;//направление вниз
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			p.sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 33, 32, 32)); 				
			
		}
			window.clear();// чистим окно
		p.update(time);// постоянная перерисовка (или если что-то еще написано в апдейт методе)

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
text.setPosition(20, 500);//задаем позицию текста
window.draw(text);//рисуем этот текст

		window.draw(p.sprite);//рисуем спрайт
		window.display();// выводим на экран
	}
	}
	return 0;
}