//Player.h
#ifndef Player_h
#define Player_h

using namespace sf;
class Player { // ����� ������
public:
float x, y, w, h, dx, dy, speed; //���������� ������ � � �, ������ � ������ ������� 
								//��������� � ��������
	int dir; //����������� ������
	std::string File; //��� �����
	Image image;//���� �����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������
	Player(std::string F, float X, float Y, float W, float H, int DIR, float SPEED);
	void update(float time);
	void interactionWithMap();
};
#endif