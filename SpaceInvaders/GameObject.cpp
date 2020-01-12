#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;


#pragma once
class GameObject {

private:
	int m_x;
	int m_y;
	int m_w;
	int m_h;
	int m_speed;


protected:
	Sprite m_sprite;
	Texture m_texture;
	SoundBuffer m_soundBufferRevive;
	SoundBuffer m_soundBufferKill;
	Sound m_soundRevive;
	Sound m_soundKill;
	bool m_isAlive;
public:

	bool isAlive() {
		return m_isAlive;
	}
	void kill() {
		m_isAlive = false;
		m_soundKill.play();
	}
	void revive() {
		m_isAlive = true;
		m_soundRevive.play();
	}

	void setSize(int w, int h) {
		m_w = w;
		m_h = h;
	}

	void draw(RenderWindow& window) {
		m_sprite.setPosition(m_x - m_w / 2, m_y);
		window.draw(m_sprite);
	}

	bool hits(GameObject& other) {
		if (&other == this) {
			return false;
		}

		if (!m_isAlive || !other.isAlive()) {
			return false;
		}
		if (m_x > other.m_x + other.m_w || other.m_x > m_x + m_w) {
			return false;
		}
		if (m_y > other.m_y + other.m_h || other.m_y > m_y + m_h) {
			return false;
		}
		return true;
	}

	void moveTo(int x, int y) {
		m_x = x;
		m_y = y;
	}

	void moveLeftRight(int dx) {
		m_x += dx;
	}

	void moveUpDown(int dy) {
		m_y += dy;
	}

	int getX() {
		return m_x;
	}

	int getY() {
		return m_y;
	}

	int getW() {
		return m_w;
	}

	int getH() {
		return m_h;
	}

	void setSpeed(int speed) {
		m_speed = speed;
	}

	int getSpeed() {
		return m_speed;
	}
};