#include "GameObject.cpp"
using namespace sf;

#pragma once
class Ship : public GameObject {

public:
	Ship() {
		setSize(20,10);
		setSpeed(5);

		m_texture.loadFromFile("ship.png");
		m_sprite.setTexture(m_texture);


	    m_soundBufferKill.loadFromFile("shipdeath.wav");
		m_soundKill.setBuffer(m_soundBufferKill);
		//m_soundBufferRevive.loadFromFile("ring.wav");
		m_soundRevive.setBuffer(m_soundBufferRevive);

		m_isAlive = true;
	}
};
