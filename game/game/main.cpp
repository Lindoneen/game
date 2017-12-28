
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <list>
#include "map.h"
#include "global.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"




//playerclass2.cpp
using namespace std;
using namespace sf;







  int main()
{
	//������ ����
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();// �������� ����� �����������
	sf::RenderWindow window(sf::VideoMode(1400, 1000, desktop.bitsPerPixel), "TANKZZZ");// ������������� ������ ���� � ����� �����������
//	camera.reset(sf::FloatRect(0,0,640,550));
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
	Image heroImage;
	
	heroImage.loadFromFile("images/hero.png");
	heroImage.createMaskFromColor(Color(255, 255, 255));
	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/Tank.png");
	easyEnemyImage.createMaskFromColor(Color(0, 0, 0));
	Player p(heroImage,50,50, 32.0, 32.0,"Player1");
	
	std::list<Entity*>  enemies; //������ ������
	std::list<Entity*>::iterator it; //�������� ����� ��������� �� ��������� ������
	const int ENEMY_COUNT = 5;	//������������ ���������� ������ � ����
    srand (time(0));
	int enemiesCount = 0;	//������� ���������� ������ � ����
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		
	float xr = 100 + rand() % 400; //��������� ���������� ����� �� ���� ���� �� ��� �x�
	float yr = 150 + rand() % 350; //��������� ���������� ����� �� ���� ���� �� ��� �y�
		//������� ������ � �������� � ������
		enemies.push_back(new Enemy(easyEnemyImage, xr, yr, 32, 32, "EasyEnemy"));
		enemiesCount += 1; //��������� ������� ������
		
	}


	int createObjectForMapTimer = 0;
	int ret = 0;
	while (window.isOpen())// ���� ���� ������� �����
	{
		
		float time = clock.getElapsedTime().asMicroseconds();// ����� ����� � �������������
		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();
		clock.restart();// ���������� ��������
		time = time / 1200;// ������������� �������� ����
		
		createObjectForMapTimer += time;//���������� ������
		if (createObjectForMapTimer>400){
			
			if (p.MaxObj<3)
			{
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

		
		
		
		    p.update(time);
			
		//�������� ������
		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			(*it)->update(time); //��������� ����� update()
		}



//			cameramap(time);
		//	window.setView(camera);

			//�������� ����������� ������ � �������
//���� ����������� ���������, �� "health = 0", ����� ��������������� � 
//��������� ��������� "you are lose"

if (p.life == true){//���� ����� ���
	for (it = enemies.begin(); it != enemies.end(); it++){//����� �� ������ ������
		if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "EasyEnemy"))
				{
					if((*it)->dx>0){
						//e��� ���� ���� � �����
						(*it)->x=p.x-100;
					}
					if((*it)->dx<0){
						(*it)->x=p.x+100;//e��� ���� ���� �����
					}
					if((*it)->dy>0){
						(*it)->x=p.x-100; //e��� ���� ���� ����
					}
					if((*it)->dy<0){
						(*it)->x=p.x+100; //e��� ���� ���� ����
					}
					std::cout << "you are lose";
				}
			}
		}
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
//text.setPosition(camera.getCenter().x-200, camera.getCenter().y-250);//������ ������� ������
window.draw(text);//������ ���� �����
if (p.life==true) 
		
		{  
		window.draw(p.sprite);//������ ������
		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			window.draw((*it)->sprite); //������ enemies �������
		}

		window.display();// ������� �� �����

       }
		else 
		
		{    
		
			CurrentExplFrame += 0.001*time;// ���������� �������� �� �� ������� ������� ������ ������, ����� ������� �� ��������� ����

			if (CurrentExplFrame > 3) CurrentExplFrame -= 3; 
			s_expl.setTextureRect(IntRect((1+33 * int(CurrentExplFrame)), 1, 32, 32)); // ����������� �� ������ �����
			s_expl.setPosition(p.GetPlayerCoordinateX(), p.GetPlayerCoordinateY());
			death_text.setString("LOL YOU DIED LOL LOL YOU DIED ");//������ ������ ������
//        death_text.setPosition(camera.getCenter().x-180, camera.getCenter().y-100);//������ ������� ������
        window.draw(death_text);//������ ���� �����
		
			window.draw(p.sprite);
			window.draw(s_expl);
			window.display();
			 
		
		}
	}
window.clear();
	return 0;
	}
	
