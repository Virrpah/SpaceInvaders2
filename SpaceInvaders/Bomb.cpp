#include "GameObject.cpp"
using namespace sf;

#pragma once
class Bomb : public GameObject {

private:

public:
	Bomb() {
		setSize(10, 20);
		setSpeed(6);
		m_texture.loadFromFile("Bomb3.png");
		m_sprite.setTexture(m_texture);
		//	m_soundBufferKill.loadFromFile("ring.wav");
		m_soundKill.setBuffer(m_soundBufferKill);
		m_soundBufferRevive.loadFromFile("bomb.wav");
		m_soundRevive.setBuffer(m_soundBufferRevive);
	}

};
