#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "SpaceInvaders.cpp"

using namespace std;

INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	Sprite m_sprite;
	Texture m_texture;
	const int screenWidth = 1920; // 1024;
	const int screenHeight = 1080; //  720;
	RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Space Invaders");
	::ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
	m_texture.loadFromFile("Background1080.png");
	m_sprite.setTexture(m_texture);

	while (true) {
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			return 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			SpaceInvaders spel;
			window.setVisible(false);
			spel.execute();
			window.setVisible(true);
		}

		Event event;
		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {
				return 0;
			}
		}

		window.clear();
		window.draw(m_sprite);
		window.display();
	}

	return 0;
}
