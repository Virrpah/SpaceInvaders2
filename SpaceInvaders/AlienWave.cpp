
#include "Ship.cpp"
#include "Missile.cpp"
#include "Alien.cpp"
#include "Bomb.cpp"
#include "Ufo.cpp"
#include "UfoBomb.cpp"
#include "HUD.cpp"
using namespace sf;

#pragma once
constexpr auto ALIENS = 55;
constexpr auto ALIENS_PER_ROW = 11;
constexpr auto PIXELS_PER_ROW = 35;


class AlienWave {

private:
	Ship m_ship;
	Missile m_missile;
	Alien m_alien[ALIENS];
	Bomb m_bomb;
	Ufo m_ufo;
	ufoBomb m_ufoBomb;
	Sprite m_sprite;
	Texture m_texture;
	HUD *m_hud;
	int m_screenWidth;
	int m_screenHeight;
	int m_ufoSpawn = 0;
public:

	AlienWave(int width, int height, HUD *hud) {
		m_screenWidth = width;
		m_screenHeight = height;
		m_bomb.kill();
		m_ufo.kill();
		m_ufoBomb.kill();
		m_ship.moveTo(m_screenWidth / 2, m_screenHeight - m_ship.getH());
		int y = PIXELS_PER_ROW;
		int x = 10;
		for (int i = 0; i < ALIENS; i++) {
			if (i % ALIENS_PER_ROW == 0) {
				y = y + PIXELS_PER_ROW;
				x = 10;
			}
			else {
				x = x + m_alien[i].getW() + 3;
			}
			m_alien[i].moveTo(x, y);
		}
		m_texture.loadFromFile("background.png");
		m_sprite.setTexture(m_texture);
		m_hud = hud;
	}

	int countAliens() {
		int count = 0;
		for (int i = 0; i < ALIENS; i++) {
			if (m_alien[i].isAlive()) {
				count++;
			}
		}
		return count;
	}
	void draw(RenderWindow& window) {
		window.draw(m_sprite);
		if (m_bomb.isAlive()) {
			m_bomb.draw(window);
		}		m_ship.draw(window);
		if (m_ufo.isAlive()) {
			m_ufo.draw(window);
		}
		for (int i = 0; i < ALIENS; i++) {
			if (m_alien[i].isAlive()) {
				m_alien[i].draw(window);
			}
		}
		if (m_missile.isAlive()) {
			m_missile.draw(window);
		}
		if (m_ufoBomb.isAlive()) {
			m_ufoBomb.draw(window);
		}

	}

	void nextFrame() {
		if (m_missile.isAlive()) {
			m_missile.moveUpDown(m_missile.getSpeed());
		}
		if (m_missile.getY() <= 0) {
			m_missile.kill();
		}
		if (m_bomb.isAlive()) {
			m_bomb.moveUpDown(m_bomb.getSpeed());
		}
		if (m_ufoBomb.isAlive()) {
			m_ufoBomb.moveUpDown(m_ufoBomb.getSpeed());
		}
		if (m_bomb.getY() >= m_screenHeight) {
			m_bomb.kill();
		}
		if (m_ufoBomb.getY() >= m_screenHeight) {
			m_ufoBomb.kill();
		}
		if (m_ufo.isAlive()) {
			m_ufo.moveLeftRight(m_ufo.getSpeed());
		}
		else
			if (countAliens() == 10 && m_ufoSpawn == 0) {
				m_ufo.moveTo(0, 50);
				m_ufo.revive();
				m_ufoSpawn++;
			}
		bool descend = false;

		if (m_missile.hits(m_ufo)) {
			m_ufo.kill();
			m_missile.kill();
			m_hud->addScore(50);
		}
		if (m_ufoBomb.hits(m_ship)) {
			m_ship.kill();
			m_ufoBomb.kill();
		}
		if (!m_ufoBomb.isAlive()) {
			if (m_ufo.getX() <= m_ship.getX() + m_ship.getW() && m_ufo.getX() >= m_ship.getX()) {
				m_ufoBomb.moveTo(m_ufo.getX(), m_ufo.getY());
				m_ufoBomb.revive();
			}
		}
		for (int i = 0; i < ALIENS; i++) {

			if (m_alien[i].isAlive()) {
				if (m_alien[i].getX() >= m_screenWidth || m_alien[i].getX() <= 0) {
					m_alien[i].turn();
					if (m_alien[i].enoughTurns(countAliens())) {
						descend = true;
					}
				}
				for (int j = 0; j < ALIENS; j++) {
					if (m_alien[i].hits(m_alien[j])) {
						m_alien[i].turn();
						m_alien[j].turn();
					}
				}
				m_alien[i].moveLeftRight(m_alien[i].getSpeed());

				if (m_missile.hits(m_alien[i])) {
					m_alien[i].kill();
					m_missile.kill();
					m_hud->addScore(10);
				}

				if (m_bomb.hits(m_ship)) {
					m_ship.kill();
					m_bomb.kill();
				}
				if (m_ufoBomb.hits(m_ship)) {
					m_ship.kill();
					m_ufoBomb.kill();
				}
				if (m_alien[i].hits(m_ship)) {
					m_ship.kill();
				}

				if (!m_bomb.isAlive()) {
					

					if (m_alien[i].getX() <= m_ship.getX() + m_ship.getW() && m_alien[i].getX() >= m_ship.getX()) {
						m_bomb.moveTo(m_alien[i].getX(), m_alien[i].getY());
						m_bomb.revive();
					}
				}

			}

		}

		if (descend) {
			for (int i = 0; i < ALIENS; i++) {
				if (m_alien[i].isAlive()) {
					m_alien[i].moveUpDown(m_alien[i].getH());
					m_alien[i].resetTurns();
				}
			}
		}
	}
	; void playerLeft() {
		if (m_ship.getX() >= m_ship.getW()) {
			m_ship.moveLeftRight(-1 * m_ship.getSpeed());
		}
	}

	void playerRight() {
		if (m_ship.getX() <= m_screenWidth - m_ship.getW()) {
			m_ship.moveLeftRight(m_ship.getSpeed());

		}
	}

	void playerShoot() {
		if (!m_missile.isAlive()) {
			m_missile.revive();
			m_missile.moveTo(m_ship.getX(), m_ship.getY());
		}
	}
	bool isAlienWaveOver() {
		if (m_ship.isAlive() && countAliens() > 0) {
			return false;
		}
		else {
			return true;
		}
	}
	bool isShipAlive() {
		return m_ship.isAlive();
	}
	void playerQuit() {
		// inget att g�ra...
	}
   
};
