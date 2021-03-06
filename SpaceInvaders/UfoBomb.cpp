#include "GameObject.cpp"
using namespace sf;

#pragma once
class ufoBomb : public GameObject {

private:

public:
	ufoBomb() {
		setSize(10, 20);
		setSpeed(6);
		m_texture.loadFromFile("Bomb2.png");
		m_sprite.setTexture(m_texture);
		//	m_soundBufferKill.loadFromFile("ring.wav");
		m_soundKill.setBuffer(m_soundBufferKill);
		m_soundBufferRevive.loadFromFile("bomb.wav");
		m_soundRevive.setBuffer(m_soundBufferRevive);
	}

};
