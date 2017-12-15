#include <SFML/Graphics.hpp>
#include <iostream> 
#include "player.h"// ���������� ��������� � �������
#include "map.h"
#include "global.h"

  int main()
{
	//������ ����
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();// �������� ����� �����������
	sf::RenderWindow window(sf::VideoMode(640, 480, desktop.bitsPerPixel), "TANKZZZ");// ������������� ������ ���� � ����� �����������
	
	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("images/tank.png");//��������� ���� ��� �����

	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������
	
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
			window.clear();// ������ ����
		p.update(time);// ���������� ����������� (��� ���� ���-�� ��� �������� � ������ ������)

		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
		if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(133, 100, 32, 32)); //����
				//��������� ������ ������, �� ������ 1-� ���������
		if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(300, 0, 32, 32));//����
				//��������� ������ s, �� ������ 2� ���������
		if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(0, 102, 32, 32));//����
				//��������� ������ 0, �� ������ 3� ���������
		if ((TileMap[i][j] == 't')) s_map.setTextureRect(IntRect(299, 101, 30, 30));//����
				//��������� ������ 0, �� ������ 3� ���������
			s_map.setPosition(j * 32, i * 32);//������������ ���������� � �����.

			window.draw(s_map);//������ ���������� �� �����
			}

	
		window.draw(p.sprite);//������ ������
		window.display();// ������� �� �����
	}
	return 0;
}