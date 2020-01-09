#include "GameObject.cpp"
using namespace sf;

#pragma once
class Missile : public GameObject {

private:

public:
	Missile() {
		setSize(10, 20);
		setSpeed(-5);
		m_texture.loadFromFile("missile.png");
		m_sprite.setTexture(m_texture);
	//	m_soundBufferKill.loadFromFile("ring.wav");
		m_soundKill.setBuffer(m_soundBufferKill);
		m_soundBufferRevive.loadFromFile("missile.wav");
		m_soundRevive.setBuffer(m_soundBufferRevive);
	}

};
