#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Game.cpp"

using namespace std;

INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	const int screenWidth = 400; // 1024;
	const int screenHeight = 300; //  720;
	const int frameRateLimit = 60;

	RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML works!");
	window.setFramerateLimit(frameRateLimit);
	Game game(screenWidth, screenHeight);
	::ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);

	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			game.playerLeft();
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			game.playerRight();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			game.playerQuit();
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			game.playerShoot();
		}

		Event event;
		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {
				window.close();
			}
		}

		window.clear();
		game.draw(window);
		window.display();
		game.nextFrame();
		window.setTitle("Space Invaders! " + to_string(game.countAliens()) + " aliens left.");
		if (game.isGameOver()) {
			window.close();
		}
	}

	return 0;
}