#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "SpaceInvaders.cpp"

using namespace std;

INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	Sprite m_sprite;
	Texture m_texture;
	const int screenWidth = 800; // 1024;
	const int screenHeight = 600; //  720;
	RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Space Invaders");
	::ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
	m_texture.loadFromFile("Background2.png");
	m_sprite.setTexture(m_texture);
		
	while (true) {
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				SpaceInvaders spel;
				spel.execute();
				//starta
			}

			Event event;
			while (window.pollEvent(event)) {

				if (event.type == Event::Closed) {
					window.close();
				}
			}

			window.clear();
			window.draw(m_sprite);
			window.display();
		}

	window.close();
	return 0;
}