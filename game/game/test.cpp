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
////////////////////////////����� ��������////////////////////////
class Entity {
public:
	enum { left, right, up, down, stay} state;// ��� ������������ - ��������� �������
	float dx, dy, x, y, speed, moveTimer;//�������� ���������� ������ ��� ������� �����
	int w, h, health; //���������� �health�, �������� ����� ������
	bool life; //���������� �life� �����, ����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������ 
	float CurrentFrame;//������ ������� ����
	std::string name;//����� ����� ���� ������, ������ ����� ��������� �� ������
	//������� ����� ���� ���� �������� � update() � ����������� �� �����

	Entity(Image &image, float X, float Y, int W, int H, std::string Name){
		x = X; y = Y; //���������� ��������� �������
		w = W; h = H; 
		name = Name; 
		moveTimer = 0;
		dx = 0; dy = 0; 
		speed = 0; 
		CurrentFrame = 0;
		health = 100;
		life = true; //���������������� ���������� ���������� �����, ����� ���
		texture.loadFromImage(image); //������� ���� ����������� � ��������
		sprite.setTexture(texture); //�������� ������ ���������
	}

FloatRect getRect(){//����� ��������� ��������������. ��� �����, ������� (���,�����).
	FloatRect FR(x, y, w, h); // ���������� FR ���� FloatRect
	return FR;
	//return FloatRect(x, y, w, h);
	//��� ������ (�����) "sf::FloatRect" ��������� ������� ������ ���������� ��������������
		//� ����� ���� ��� ���������� �������� ������������ ����� �� �����
		//����� ��� �������� ��������, ���� �� ��� �����-���� ���� �� ���� ����� 
		//��� �-��� ����� ��� �������� ����������� 
	}
	virtual void update(float time) = 0;
};

class Player: public Entity{ // ����� ������


public:
	 int playerScore;
    int MaxObj;
 
	




Player(Image &image,float X, float Y, float W, float H,std::string Name) : Entity(image,X,Y,W,H,Name)
{ 
	playerScore=0;
	MaxObj=0;
	state=stay;
	if (name=="Player1"){
 

	sprite.setTextureRect(IntRect(33, 0, w, h)); //������������� ��� �������

	
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
for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
	for (int j = x / 32; j<(x + w) / 32; j++)
	{
		if (TileMap[i][j] == '0')//���� ������� ������ �����
		{
		if (Dy > 0) { y = i * 32 - h;  dy = 0; }//�� Y 
		if (Dy < 0) { y = i * 32 + 32; dy = 0; }//������������ � �������� ������ �����
		if (Dx > 0) { x = j * 32 - w; dx = 0; }//� ������ ����� �����
		if (Dx < 0) { x = j * 32 + 32; dx = 0; }// � ����� ����� �����
		}	
		if (TileMap[i][j] == 's') {
			health -= 40; //���� ����� ������, ���������� playerScore=playerScore+1;
			TileMap[i][j] = ' ';
		}
		
	}
}


void update(float time) //������� ��������� ������� ������. ��������� � ���� float time -
	//����� SFML, ���������� ���� �������� ����������, ����� ��������� ��������.
{
	if (life) {//���������, ��� �� �����
		control();//������� ���������� ����������
		switch (state)//��� �������� ��������� �������� � ����������� �� ���������
		{
		case right:{
			dx=speed;
			dy=0;
			CurrentFrame += 0.005*time;// ���������� �������� �� �� ������� ������� ������ ������, ����� ������� �� ��������� ����
			
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 66, 32, 32)); 			
			getPlayerCamera(GetPlayerCoordinateX(),GetPlayerCoordinateY());
			break;
			}
         case left:{//��������� ���� �����
			dx = -speed;
			dy=0;
		CurrentFrame += 0.005*time;
		// ���������� �������� �� �� ������� ������� ������ ������, ����� ������� �� ��������� ����

			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 99, 32, 32)); // ����������� �� ������ �����
			getPlayerCamera(GetPlayerCoordinateX(),GetPlayerCoordinateY());
			break;
			}
		case up:{//���� �����
			dx = 0;
			dy = -speed;
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 0, 32, 32));			
			 getPlayerCamera(GetPlayerCoordinateX(),GetPlayerCoordinateY());
			break;
			}
		case down:{//���� ����
			dx = 0;
			dy = speed;
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 33, 32, 32)); 				
			getPlayerCamera(GetPlayerCoordinateX(),GetPlayerCoordinateY());
			break;
			}
				  if (speed=0) state=stay;
		case stay:{//�����
			dy = speed;
			dx = speed;
			break;
			}

		}

        x += dx*time; //�������� �� �X�
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �

		y += dy*time; //�������� �� �Y�
		checkCollisionWithMap(0, dy);//������������ ������������ �� Y

		speed = 0;    //�������� ��������, ����� �������� �����������.
		state = stay; //��������� - �����

		sprite.setPosition(x, y); //������������ ������ � ����� ������� (x, y).

		if (health <= 0){ life = false; }//���� ������ ������ 0, ���� ����� 0, �� ������� 
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
			if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� �0�
					//(�����), �� ��������� "����������� ��������" ���������:
		{
			if (dy>0) {//���� �� ��� ����,
			y = i * 32 - h;//�� �������� (-h) ���������� �y� ���������. 
				//������� �������� ���������� �i� ������ ���������� �� ����� � 
				//����� �������� �� ������ ������� ���������.
			}
			if (dy<0){
			y = i * 32 + 32;//���������� � ��������� �����.	
			}
			if (dx>0){
			x = j * 32 - w;//���� ���� ������, �� ���������� �x� ����� 
							//����� (������ 0) ����� ������ ���������
			}
			if (dx < 0){
			x = j * 32 + 32; //���������� ���� �����
			}
		}	
			if (TileMap[i][j] == 's') 
			{ //���� ������ ����� 's' (������)
				health -= 40;
				MaxObj-=1;
				TileMap[i][j] = ' ';//������� ������
			}
	}
		

}

};

class Enemy :public Entity{
public:
	int direction;//����������� �������� �����
Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name){
	if (name == "EasyEnemy"){
		//������ ������� ���� ������������� ���
		//������ ������ ������. IntRect � ��� ���������� �����
		sprite.setTextureRect(IntRect(332, 135, w, h));
		direction = rand() % (3); //����������� �������� ����� ����� ��������� �������
			//����� ��������� ��������� �����
			speed = 0.1;//���� ��������.���� ������ ������ ���������
			dx = speed;
		}
	}

void checkCollisionWithMap(float Dx, float Dy)//�-��� �������� ������������ � ������
	{
	for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
		if (TileMap[i][j] == '0')//���� ������� - ������ �����
			{
			if (Dy > 0) { y = i * 32 - h;  dy = -0.1; 
					direction = rand() % (3); //����������� �������� �����
						}//�� Y 
			if (Dy < 0) { y = i * 32 + 32; dy = 0.1;  
					direction = rand() % (3);//����������� �������� ����� 
						}//������������ � �������� ������ 
			if (Dx > 0) { x = j * 32 - w; dx = -0.1;  
					direction = rand() % (3);//����������� �������� ����� 
						}//� ������ ����� �����
					if (Dx < 0) { x = j * 32 + 32; dx = 0.1;  
					direction = rand() % (3); //����������� �������� �����
						}// � ����� ����� �����
				}
			}
	}

	void update(float time)
	{
		if (name == "EasyEnemy"){//��� ��������� � ����� ������ ������ ����� �����

		if (life) {//���������, ��� �� �����
		switch (direction)//�������� ��������� �������� � ����������� �� ���������
		{
		case right:{
			dx=speed;
			dy=0;
			CurrentFrame += 0.005*time;// ���������� �������� �� �� ������� ������� ������ ������, ����� ������� �� ��������� ����
			
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((330+33 * int(CurrentFrame)), 201, 32, 32)); 			
			
			break;
			}
         case left:{//��������� ���� �����
			dx = -speed;
			dy=0;
		CurrentFrame += 0.005*time;
		// ���������� �������� �� �� ������� ������� ������ ������, ����� ������� �� ��������� ����

			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((330+33 * int(CurrentFrame)), 234, 32, 32)); // ����������� �� ������ �����
			
			break;
			}
		case up:{//���� �����
			dx = 0;
			dy = -speed;
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((330+33 * int(CurrentFrame)), 134, 32, 32));			
			
			break;
			}
		case down:{//���� ����
			dx = 0;
			dy = speed;
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((330+33 * int(CurrentFrame)), 167 , 32, 32)); 				
			
			break;
			}
				  if (speed=0) state=stay;
		case stay:{//�����
			dy = speed;
			dx = speed;
			break;
			}

		}
		}

		x += dx*time; //�������� �� �X�
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �

		y += dy*time; //�������� �� �Y�
		checkCollisionWithMap(0, dy);//������������ ������������ �� Y

		sprite.setPosition(x, y); //������ � ������� (x, y).

		if (health <= 0){ life = false; }//���� ������ ������ 0, ���� ����� 0, �� �������
		}
		}
	};
//����� Enemy ������

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
	Image heroImage;
	
	heroImage.loadFromFile("images/hero.png");
	heroImage.createMaskFromColor(Color(255, 255, 255));
	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/Tank.png");
	easyEnemyImage.createMaskFromColor(Color(0, 0, 0));
	Player p(heroImage,50,50, 32.0, 32.0,"Player1");
	
	std::list<Entity*>  enemies; //������ ������
	std::list<Entity*>::iterator it; //�������� ����� ��������� �� ��������� ������
	const int ENEMY_COUNT = 3;	//������������ ���������� ������ � ����
    
	int enemiesCount = 0;	//������� ���������� ������ � ����
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
	float xr = 150 + rand() % 500; //��������� ���������� ����� �� ���� ���� �� ��� �x�
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
		time = time / 800;// ������������� �������� ����
		
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



			cameramap(time);
			window.setView(camera);

			//�������� ����������� ������ � �������
//���� ����������� ���������, �� "health = 0", ����� ��������������� � 
//��������� ��������� "you are lose"

if (p.life == true){//���� ����� ���
	for (it = enemies.begin(); it != enemies.end(); it++){//����� �� ������ ������
		if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "EasyEnemy"))
				{
					p.health = 0;
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
text.setPosition(camera.getCenter().x-200, camera.getCenter().y-250);//������ ������� ������
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
        death_text.setPosition(camera.getCenter().x-180, camera.getCenter().y-100);//������ ������� ������
        window.draw(death_text);//������ ���� �����
		
			window.draw(p.sprite);
			window.draw(s_expl);
			window.display();
			 
		
		}
	}
window.clear();
	return 0;
	}
	
