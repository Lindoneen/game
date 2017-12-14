#include <SFML/Graphics.hpp>
#include "player.h"

//playerclass2.cpp

using namespace sf;


Player::Player(std::string F, float X, float Y, float W, float H, int DIR, float SPEED)
{ 
	File = F; //��� �����
	w = W; h = H; //������ � ������ �������
	dir=DIR; speed=SPEED;
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
			
}
   