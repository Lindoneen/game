#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "player.h"// ���������� ��������� � �������
#include "map.h"
#include "global.h"
#include "Camera.h"

using namespace std;
  int main()
{
	//������ ����
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();// �������� ����� �����������
	sf::RenderWindow window(sf::VideoMode(640, 550, desktop.bitsPerPixel), "TANKZZZ");// ������������� ������ ���� � ����� �����������
	camera.reset(sf::FloatRect(0,0,640,550));
	Font font;//����� 
	Font death_font;
	death_font.loadFromFile("CHILLER.ttf");
    font.loadFromFile("CyrilicOld.ttf");//�������� ������ ������ ���� ������
Text text("", font, 20);//������� ������ �����. ������ ������(� ��������);
//��� ������ ����� (�� ������)
text.setColor(Color::Red);//��������� ����� � �������.
text.setStyle(Text::Bold);//������ �����.

Text death_text("", death_font, 40);
death_text.setColor(Color::Black);
death_text.setStyle(Text::Bold);


	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("images/tank.png");//��������� ���� ��� �����

	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������

	Image expl_image;
	expl_image.loadFromFile("images/tank.png" );//��������� �����������

    expl_image.createMaskFromColor(Color(0, 0, 0));// ������� ����� ���

	Texture expl;
	expl.loadFromImage(expl_image); // ��������� ����������� � ��������

	Sprite s_expl;
	s_expl.setTexture(expl);
	


	float CurrentExplFrame= 0;
	float CurrentFrame = 0;//������ ������� ����
	Clock clock;
	Clock gameTimeClock;//���������� �������� �������, ����� ����� ������� ����� ���� 
	int gameTime = 0;

	Player p("hero.png", 32.0, 32.0, 0, 0.0);// ��������� ����������
	int createObjectForMapTimer = 0;
	int ret = 0;
	while (window.isOpen())// ���� ���� ������� �����
	{
		
		float time = clock.getElapsedTime().asMicroseconds();// ����� ����� � �������������
		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();
		clock.restart();// ���������� ��������
		time = time / 800;// ������������� �������� ����

		createObjectForMapTimer += time;//���������� ������
		if (createObjectForMapTimer>100){
			
			if (p.MaxObj<3){
				p.MaxObj+=1;
			    ret=p.MaxObj;
			randomMapGenerate();//���������  ������
	        createObjectForMapTimer = 0;//�������� ������
			}
			else {
				createObjectForMapTimer = 0;
			}
			cout << ret;
		}
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)// ���� �� ���� ������ ������� ���� ������������
				window.close();
		} // ��

		
		
		if (p.life) {
		//�������� �� ������� ������
	if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
		p.dir = 1; p.speed = 0.1;
		
		
		CurrentFrame += 0.005*time;// ���������� �������� �� �� ������� ������� ������ ������, ����� ������� �� ��������� ����

			if (CurrentFrame > 8) CurrentFrame -= 8; 
			p.sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 99, 32, 32)); // ����������� �� ������ �����
			getPlayerCamera(p.GetPlayerCoordinateX(),p.GetPlayerCoordinateY());
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || 
	 	 	 	 	 	 	 (Keyboard::isKeyPressed(Keyboard::D)))) {	
								 p.dir = 0; p.speed = 0.1;//����������� ������
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			p.sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 66, 32, 32)); 			
			getPlayerCamera(p.GetPlayerCoordinateX(),p.GetPlayerCoordinateY());
	      

		}

		if ((Keyboard::isKeyPressed(Keyboard::Up) || 
	 	 	 	 	 	 	 (Keyboard::isKeyPressed(Keyboard::W)))) {
								 p.dir = 3; p.speed = 0.1;//����������� �����
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			p.sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 0, 32, 32));			
			 getPlayerCamera(p.GetPlayerCoordinateX(),p.GetPlayerCoordinateY());
		}

		if ((Keyboard::isKeyPressed(Keyboard::Down) || 
	 	 	 	 	 	 	 (Keyboard::isKeyPressed(Keyboard::S)))) {
								 p.dir = 2; p.speed = 0.1;//����������� ����
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			p.sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 33, 32, 32)); 				
			getPlayerCamera(p.GetPlayerCoordinateX(),p.GetPlayerCoordinateY());
		}
		    p.update(time);// ���������� ����������� (��� ���� ���-�� ��� �������� � ������ ������)
			cameramap(time);
			window.setView(camera);
			window.clear();// ������ ����
		                 

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

		
	std::ostringstream playerHealthString, gameTimeString;//�������� ���������� �������� � �������
playerHealthString << p.health; gameTimeString << gameTime;//��������� ������
text.setString("��������: " + playerHealthString.str() + "\n����� ����: " + gameTimeString.str());//������ ������ ������
text.setPosition(camera.getCenter().x-200, camera.getCenter().y-250);//������ ������� ������
window.draw(text);//������ ���� �����

		window.draw(p.sprite);//������ ������
		window.display();// ������� �� �����

	}
		else
		{    
		
			CurrentExplFrame += 0.001*time;// ���������� �������� �� �� ������� ������� ������ ������, ����� ������� �� ��������� ����

			if (CurrentExplFrame > 3) CurrentExplFrame -= 3; 
			s_expl.setTextureRect(IntRect((1+33 * int(CurrentExplFrame)), 1, 32, 32)); // ����������� �� ������ �����
			s_expl.setPosition(p.GetPlayerCoordinateX(), p.GetPlayerCoordinateY());
			window.draw(s_expl);
			window.display();
			 
		death_text.setString("LOL YOU DIED LOL LOL YOU DIED ");//������ ������ ������
        death_text.setPosition(camera.getCenter().x-180, camera.getCenter().y-100);//������ ������� ������
        window.draw(death_text);//������ ���� �����
		
		}
	

	}
	window.clear();
	return 0;
}