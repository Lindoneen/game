#include <SFML/Graphics.hpp>
#include <iostream> 
#include "player.h"// ���������� ��������� � �������


  int main()
{
	//������ ����
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();// �������� ����� �����������
	sf::RenderWindow window(sf::VideoMode(600, 480, desktop.bitsPerPixel), "TANKZZZ");// ������������� ������ ���� � ����� �����������

	
	float CurrentFrame = 0;//������ ������� ����
	Clock clock;
	Player p("hero.png", 250, 250, 32.0, 32.0, 0, 0.0);// ��������� ����������

	while (window.isOpen())// ���� ���� ������� �����
	{
		float time = clock.getElapsedTime().asMicroseconds();// ����� ����� � �������������
		clock.restart();// ���������� ��������
		time = time / 800;// ������������� �������� ����

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)// ���� �� ���� ������ ������� ���� ������������
				window.close();
		} // ��

		//�������� �� ������� ������
	if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
		p.dir = 1; p.speed = 0.1;
 	

		CurrentFrame += 0.005*time;// ���������� �������� �� �� ������� ������� ������ ������, ����� ������� �� ��������� ����

			if (CurrentFrame > 8) CurrentFrame -= 8; 
			p.sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 99, 32, 32)); // ����������� �� ������ �����
			
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || 
	 	 	 	 	 	 	 (Keyboard::isKeyPressed(Keyboard::D)))) {	
								 p.dir = 0; p.speed = 0.1;//����������� ������
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			p.sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 66, 32, 32)); 			

	

		}

		if ((Keyboard::isKeyPressed(Keyboard::Up) || 
	 	 	 	 	 	 	 (Keyboard::isKeyPressed(Keyboard::W)))) {
								 p.dir = 3; p.speed = 0.1;//����������� �����
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			p.sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 0, 32, 32));			
			 
		}

		if ((Keyboard::isKeyPressed(Keyboard::Down) || 
	 	 	 	 	 	 	 (Keyboard::isKeyPressed(Keyboard::S)))) {
								 p.dir = 2; p.speed = 0.1;//����������� ����
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			p.sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 33, 32, 32)); 				
			
		}
		p.update(time);// ���������� ����������� (��� ���� ���-�� ��� �������� � ������ ������)

		window.clear();// ������ ����
		window.draw(p.sprite);//������ ������
		window.display();// ������� �� �����
	}
	return 0;
}