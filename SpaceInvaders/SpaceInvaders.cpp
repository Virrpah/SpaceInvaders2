#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "AlienWave.cpp"

using namespace std;

INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	constexpr auto FRAMERATE_INCREASE = 5;
	const int screenWidth = 400; // 1024;
	const int screenHeight = 300; //  720;
	int frameRateLimit = 60;
	int lives = 3;
	RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Space Invaders");
	::ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);

	while(lives > 0) {
		window.setFramerateLimit(frameRateLimit);
		AlienWave wave(screenWidth, screenHeight);

		while (!wave.isAlienWaveOver()) {
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				wave.playerLeft();
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				wave.playerRight();
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				wave.playerQuit();
				window.close();
				lives = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				wave.playerShoot();
			}

			Event event;
			while (window.pollEvent(event)) {

				if (event.type == Event::Closed) {
					window.close();
					lives = 0;
				}
			}

			window.clear();
			wave.draw(window);
			window.display();
			wave.nextFrame();
			window.setTitle("Space Invaders! " + to_string(wave.countAliens()) + " aliens left.");
			
		}
		if (!wave.isShipAlive()) {
			lives--;
		}
		frameRateLimit += FRAMERATE_INCREASE;
	}
	window.close();
	
	return 0;
}