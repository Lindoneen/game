//Player.h
#ifndef Player_h
#define Player_h

using namespace sf;
class Player { // ����� ������
private: 
float x, y;
public:
float w, h, dx, dy, speed; //���������� ������ � � �, ������ � ������ �������
								//��������� � ��������
    int MaxObj;
	int dir, health; 
	bool life;
	std::string File; //��� �����
	Image image;//���� �����������
    Texture expl;
	Sprite s_expl;
	Texture texture;//���� ��������
	Sprite sprite;//���� ������
	Player(std::string F, float W, float H, int DIR, float SPEED);
	void update(float time);
	void interactionWithMap();
	float GetPlayerCoordinateX();
	float GetPlayerCoordinateY();
	
};
#endif