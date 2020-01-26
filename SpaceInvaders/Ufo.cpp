#include "GameObject.cpp"
using namespace sf;

#pragma once
class Ufo : public GameObject {

private:

public:
	Ufo() {
		setSize(105, 65);
		setSpeed(5);
		m_texture.loadFromFile("ufo.png");
		m_sprite.setTexture(m_texture);
		m_soundBufferKill.loadFromFile("pop.wav");
		m_soundKill.setBuffer(m_soundBufferKill);
		m_soundBufferRevive.loadFromFile("bomb.wav");
		m_soundRevive.setBuffer(m_soundBufferRevive);
	}

};
