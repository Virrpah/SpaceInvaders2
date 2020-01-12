#include "GameObject.cpp"
#include <random>
using namespace sf;
using namespace std;

#pragma once
class Alien : public GameObject {

private:
	int m_turns = 0;
public:
	Alien() {
		setSize(39, 30);
		setSpeed(2);
		m_texture.loadFromFile("alien2.png");
		m_sprite.setTexture(m_texture);
		m_sprite.setColor(randomColor());
		m_soundBufferKill.loadFromFile("pop.wav");
		m_soundKill.setBuffer(m_soundBufferKill);
		m_soundBufferRevive.loadFromFile("ring.wav");
		m_soundRevive.setBuffer(m_soundBufferRevive);
		m_isAlive = true;
	}


	void turn() {
		setSpeed(getSpeed() * -1);
		m_turns++;
	}

	void resetTurns() {
		m_turns = 0;
	}

	bool enoughTurns(int aliens) {
		return m_turns >= aliens;
	}

	Color randomColor() {

		std::random_device rd;     // only used once to initialise (seed) engine
		std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
		std::uniform_int_distribution<int> uni(0, 255); // guaranteed unbiased

		return Color(uni(rng), uni(rng), uni(rng));

	}


};