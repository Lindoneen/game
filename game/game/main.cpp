#include <SFML/Graphics.hpp>
#include <iostream> 
#include "player.h"// подключаем заголовок с классом


  int main()
{
	//Создаём окно
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();// получаем режим отображения
	sf::RenderWindow window(sf::VideoMode(600, 480, desktop.bitsPerPixel), "TANKZZZ");// устанавливаем размер окна и режим отображения

	
	float CurrentFrame = 0;//хранит текущий кадр
	Clock clock;
	Player p("hero.png", 250, 250, 32.0, 32.0, 0, 0.0);// Начальные координаты

	while (window.isOpen())// пока окно открыто делай
	{
		float time = clock.getElapsedTime().asMicroseconds();// взять время в микросекундах
		clock.restart();// перезапуск счетчика
		time = time / 800;// устанавливаем скорость игры

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)// если на окно нажать закрыть цикл прекратиться
				window.close();
		} // всё

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
		p.update(time);// постоянная перерисовка (или если что-то еще написано в апдейт методе)

		window.clear();// чистим окно
		window.draw(p.sprite);//рисуем спрайт
		window.display();// выводим на экран
	}
	return 0;
}