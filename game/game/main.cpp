#include <SFML/Graphics.hpp>
#include <iostream> 

using namespace sf;
int main()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(640, 480, desktop.bitsPerPixel), "Lesson 6");

	Texture herotexture;
	herotexture.loadFromFile("images/hero.png");

	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(0, 0, 32, 32));
	herosprite.setPosition(250, 250);

	float CurrentFrame = 0;//������ ������� ����
	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

/////////////////////////////���������� ���������� � ���������///////////////////////////////
	if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) { 	//���� ������ ������� ������� ����� ��� ���� ����� �
		CurrentFrame += 0.005*time;
//������ ��� ����������� �� "������". ���������� ������� �� ����, �������� ������������ //������� � ��������. ������� 0.005, ����� �������� �������� ��������
			if (CurrentFrame > 8) CurrentFrame -= 8; //���� ������ � �������� ����� - //������������ �����.
			herosprite.setTextureRect(IntRect(33 * int(CurrentFrame), 99, 32, 32)); //�������� �� ����������� �. ����������, ��� �������� ��������� � ���������� � ������ //0,96,96*2, � ����� 0
			herosprite.move(-0.1*time, 0); //���������� �������� ��������� �����
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || 
	 	 	 	 	 	 	 (Keyboard::isKeyPressed(Keyboard::D)))) {
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			herosprite.setTextureRect(IntRect(33 * int(CurrentFrame), 66, 32, 32)); 				//�������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96

			herosprite.move(0.1*time, 0); //�������� ��������� ������

		}

		if ((Keyboard::isKeyPressed(Keyboard::Up) || 
	 	 	 	 	 	 	 (Keyboard::isKeyPressed(Keyboard::W)))) {
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			herosprite.setTextureRect(IntRect(33 * int(CurrentFrame), 0, 32, 32)); 				//�������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96
			herosprite.move(0, -0.1*time); //�������� ��������� �����
		}

		if ((Keyboard::isKeyPressed(Keyboard::Down) || 
	 	 	 	 	 	 	 (Keyboard::isKeyPressed(Keyboard::S)))) {
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			herosprite.setTextureRect(IntRect(33 * int(CurrentFrame), 33, 32, 32)); 				//�������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96
			herosprite.move(0, 0.1*time); // �������� ��������� ����
		}
		window.clear();
		window.draw(herosprite);
		window.display();
	}
	return 0;
}
