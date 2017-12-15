#include <SFML/Graphics.hpp>
#include "player.h"
#include "map.h"
#include "global.h"

//playerclass2.cpp

using namespace sf;


Player::Player(std::string F, float X, float Y, float W, float H, int DIR, float SPEED)
{ 
	File = F; //��� �����
	w = W; h = H; //������ � ������ �������
	dir=DIR; speed=SPEED;
	health = 100;
		//���������������� ���������� ����� � ������������
	life = true;//���������������� ���������� ���������� �����
	image.loadFromFile("images/" + File);//��������� �����������
    image.createMaskFromColor(Color(255, 255, 255));// ������� ����� ���
	texture.loadFromImage(image); // ��������� ����������� � ��������
	sprite.setTexture(texture); //�������� ������ ���������
	x = X; y = Y; // ��������� ����������
	sprite.setTextureRect(IntRect(33, 0, w, h)); //������������� ��� �������
}


void Player::update(float time) //������� ��������� ������� ������. ��������� � ���� float time -
	//����� SFML, ���������� ���� �������� ����������, ����� ��������� ��������.
{
	switch (dir)//���� �������� �� X Y � ����������� �� �����������
	{
	case 0: dx = speed; dy = 0; break; //�������� �� X ������
	case 1: dx = -speed; dy = 0; break;//�� X �����
	case 2: dx = 0; dy = speed; break;//�� Y ����
	case 3: dx = 0; dy = -speed; break;//�� Y �����
	}

	x += dx*time; //�������� �� X
	y += dy*time; //�������� �� Y
	speed = 0;    //�������� ��������, ����� �������� �����������.
	sprite.setPosition(x, y); //������� ������ � ������� (x, y). 
	interactionWithMap();	
	if (health <= 0){ life = false;}
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
			if (TileMap[i][j] == 's') { //���� ������ ����� 's' (������)
				health -= 40;
				x = 300; y = 300;//�����-�� ��������...������������ �����
				TileMap[i][j] = ' ';//������� ������
			}
	}

};



