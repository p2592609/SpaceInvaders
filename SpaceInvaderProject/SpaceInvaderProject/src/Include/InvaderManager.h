#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Include/Invaders.h"
#include"Include/Bullet.h"

using CollisionResult = std::pair<int, std::vector<sf::Vector2f>>;

class InvaderManager
{
private:

	//vector for invader class
	std::vector<Invaders> InvadersV;

	//clock and time variables
	sf::Clock timer;
	sf::Time elapsedTime;
	
	//method to check invaders position
	bool testInvaderPosition(const Invaders& invader);
	//variable for if invaders are moving left and invaders should move down
	bool m_isMovingLeft = false;
	bool m_moveDown = false;

	//variables for how many invaders are alive
	unsigned m_aliveInvaders = 24;
	bool m_allInvadersAlive;
	//variable for if game is over
	bool iGameOver = false;

public:
	//constructor
	InvaderManager();
	//method for drawing all invaders
	void drawInvaders(sf::RenderTarget& target);
	//method for moving all invaders
	void invaderStep();
	//method for checking if invaders collide with bullets
	CollisionResult tryCollideWithBullets(std::vector<Bullet>& bullets);
	//method for getting random lowest down invader
	sf::Vector2f getRandomLowestInvaderPoint();
	//method for checking if all invaders are alive
	bool allInvadersAlive();
	//method for adding invaders
	void addInvaders();
	//method for setting the game to be over
	bool setGameOver();
};