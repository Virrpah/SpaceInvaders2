#include "GameObject.cpp"
using namespace sf;

#pragma once
class Alien : public GameObject {

private:
	int m_turns = 0;
public:
	Alien() {
		setSize(10, 20);
		setSpeed(2);
		m_texture.loadFromFile("alien.png");
		m_sprite.setTexture(m_texture);
		m_soundBufferKill.loadFromFile("pop.wav");
		m_soundKill.setBuffer(m_soundBufferKill);
		m_soundBufferRevive.loadFromFile("ring.wav");
		m_soundRevive.setBuffer(m_soundBufferRevive);
	}

	bool turn(int aliens) {
		if (m_turns < aliens) {
			setSpeed(getSpeed() * -1);
			m_turns++;
			return true;
		} else {
			m_turns = 0;
			return false;
		}
	}

};