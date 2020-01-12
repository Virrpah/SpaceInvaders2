
#include "Ship.cpp"
#include "Missile.cpp"
#include "Alien.cpp"
#include "Bomb.cpp"
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
	Sprite m_sprite;
	Texture m_texture;
	int m_screenWidth;
	int m_screenHeight;
public:

	AlienWave(int width, int height) {
		m_screenWidth = width;
		m_screenHeight = height;
		m_bomb.kill();
		m_ship.moveTo(m_screenWidth / 2, m_screenHeight - m_ship.getH());
		int y = PIXELS_PER_ROW;
		int x = 10;
		for (int i = 0; i < ALIENS; i++) {
			if (i % ALIENS_PER_ROW == 0) {
				y = y + PIXELS_PER_ROW;
				x = 10;
			} else {
				x = x + m_alien[i].getW() + 3;
			}
			m_alien[i].moveTo(x, y);
		}
		m_texture.loadFromFile("background.png");
		m_sprite.setTexture(m_texture);

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
		for (int i = 0; i < ALIENS; i++) {
			if (m_alien[i].isAlive()) {
				m_alien[i].draw(window);
			}
		}
		if (m_missile.isAlive()) {
			m_missile.draw(window);
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
		if (m_bomb.getY() >= m_screenHeight) {
			m_bomb.kill();
		}
		bool descend = false;
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
				}
				if (m_bomb.hits(m_ship)) {
					m_ship.kill();
					m_bomb.kill();
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
	void playerLeft() {
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
		} else {
			return true;
		}
	}
	bool isShipAlive() {
		return m_ship.isAlive();
	}
	void playerQuit() {
		// inget att göra...
	}
};

