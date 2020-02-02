#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

using namespace sf;
using namespace std;

#pragma once
class HUD {
private: 
	int m_score = 0;
	int m_level;
	int m_lives;
	int m_highscore = 0;
	Font m_font;

public:
	HUD() {
		m_font.loadFromFile("Games.ttf");
		readHighscore();
		
	}
	void draw(RenderWindow& window) {

		Text leftText("Level: " + to_string(m_level) + "\n" + "Lives: " + to_string(m_lives), m_font);
		leftText.setCharacterSize(20);
		leftText.setFillColor(Color::Red);
		leftText.setPosition(700, 550);
		window.draw(leftText);
		Text rightText("Highscore: " + to_string(m_highscore) + "\n" + "Score: " + to_string(m_score), m_font);
		rightText.setCharacterSize(20);
		rightText.setFillColor(Color::Red);
		rightText.setPosition(0, 550);
		window.draw(rightText);
	}

	void setScore(int score){
		m_score = score;
		if (m_score > m_highscore) {
			m_highscore = m_score;
		}

	}

	void addScore(int score) {
		m_score += score;
		if (m_score > m_highscore) {
			m_highscore = m_score;
		}
	}
	void setLevel(int level) {
		m_level = level;
	}
	void setLives(int lives) {
		m_lives = lives;
	}

	void saveHighscore() {
		ofstream fout("spaceinvaders.hiscore");
		fout << m_highscore;
		fout.close();

	}
	void readHighscore() {
		ifstream fin("spaceinvaders.hiscore");
		
		fin >> m_highscore;
		fin.close();
	}


};