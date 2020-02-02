#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "AlienWave.cpp"
#include "HUD.cpp"

#pragma once
using namespace std;
class SpaceInvaders {

public: 

	void execute() {
		constexpr auto FRAMERATE_INCREASE = 5;
		const int screenWidth = 800; // 1024;
		const int screenHeight = 600; //  720;
		int frameRateLimit = 60;
		int lives = 3;
		int wavenumber = 1;
		RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Space Invaders");
		::ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
		HUD hud;
		hud.setLives(lives);
		hud.setLevel(wavenumber);
		while (lives > 0) {
			window.setFramerateLimit(frameRateLimit);
			AlienWave wave(screenWidth, screenHeight, &hud);
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
				hud.draw(window);
				window.display();
				wave.nextFrame();
				window.setTitle("Space Invaders! Current level: " + to_string(wavenumber));

			}
			if (!wave.isShipAlive()) {
				lives--;
				hud.setLives(lives);
			}
			else {
				frameRateLimit += FRAMERATE_INCREASE;
				wavenumber++;
				hud.setLevel(wavenumber);
			}
		}
		hud.saveHighscore();
		window.close();
	}
};