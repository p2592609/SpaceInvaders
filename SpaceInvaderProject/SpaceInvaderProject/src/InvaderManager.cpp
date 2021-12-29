
#include "Include/InvaderManager.h"
#include<iostream>

InvaderManager::InvaderManager() 
	: elapsedTime (sf::seconds(1))
{
	////adds invaders into a vector and sets their initial position
	////gap between invaders
	//const int GAP = 10;
	////rows
	//for (int y = 0; y < 3; y++)
	//{
	//	//coloumns
	//	for (int x = 0; x < 8; x++)
	//	{
	//		//invaders x value
	//		float invaderX = x * 50 + (GAP * x) + 50;
	//		//invaders y value
	//		float invaderY = y * 50 + (GAP * y) + 50;
	//		InvadersV.emplace_back(sf::Vector2f{ invaderX, invaderY });
	//	}
	//}
}

//draws all invaders
void InvaderManager::drawInvaders(sf::RenderTarget& target)
{
	//loop to go throw invader vector 
	for (auto& invaders : InvadersV)
	{
		//if invader is alive draw invader
		if (!invaders.isAlive()) continue;
		invaders.draw(target);
	}
	
}

//moves all invaders
void InvaderManager::invaderStep()
{
	//if to set the time between a step
	if (timer.getElapsedTime() > elapsedTime)
	{
		//local variables for moving down and checking which direction to move
		bool moveDown = false;
		float step = m_isMovingLeft ? -25.0f : 25.0f;
		//if movedown is true step equals to -1
		if (m_moveDown) {
			step *= -1;
		}
		//loop through invader vector
		for (auto& invaders : InvadersV) {
			//if invader is alive move a step
			if (!invaders.isAlive()) continue;
			invaders.move(step, 0.0f);
			//if movedown is true move all invaders down in the y position
			if (m_moveDown) {
				invaders.move(0, Invaders::HEIGHT / 2.0f);
			}
			//if moveDown is false calls testInvaderPosition method
			else if (!moveDown) {
				moveDown = testInvaderPosition(invaders);
			}
		}
		//if movedown is true then invaders move the oppisite direction
		if (m_moveDown) m_isMovingLeft = !m_isMovingLeft;
		m_moveDown = moveDown;
		timer.restart();
	}
}

//checks if invaders collide with lasers
CollisionResult InvaderManager::tryCollideWithBullets(std::vector<Bullet>& bullets)
{
	CollisionResult result;
	
	//for loops to go throw laser and invader vectors
	for (auto& projectile : bullets) {
		for (auto& invader : InvadersV) {
			//if invader is not alive and laser is not active continue
			if (!invader.isAlive() || !projectile.isActive())
				continue;
			//if laser collides with invader
			if (projectile.tryCollideWith(invader)) {
				//alive invaders decrements
				m_aliveInvaders--;
				std::cout << m_aliveInvaders;
				//checks if invaders are dead
				if (m_aliveInvaders == 0) {
					//sets all invaders alive to false
					m_allInvadersAlive = false;
				}
				result.first += 100;
				std::cout << result.first;
				//gets invader's position and put it into second result vector
				result.second.emplace_back(invader.getPosition());
				//adds 100 to first result vector
				
				}
			}
		}

	//returns result vector
		return result;
}

//gets a lowest random invander
sf::Vector2f InvaderManager::getRandomLowestInvaderPoint()
{
	
	//Keep looping until an invader is found
	while (true) {
		//checks a random coloumn
		auto invaderColumn = rand() % 7;
		//checks for lowest invader on that column
		for (int y = 2; y >= 0; y--) {
			int index = y * 8 + invaderColumn;
			//gets invader at that position
			auto& invaders = InvadersV.at(index);
			//cghecks if invader is alive
			if (invaders.isAlive()) 
			{
				return
				{
					//transform to below the invader's center
					invaders.getPosition().x + Invaders::WIDTH / 2,
					invaders.getPosition().y + Invaders::HEIGHT + 50
				};
			}
		}
	}
}

//adds invaders
void InvaderManager::addInvaders()
{
	InvadersV.clear();
	//adds invaders into a vector and sets their initial position
	//gap between invaders
	const int GAP = 10;
	//rows
	for (int y = 0; y < 3; y++)
	{
		//coloumns
		for (int x = 0; x < 8; x++)
		{
			//invaders x value
			float invaderX = x * 50 + (GAP * x) + 50;
			//invaders y value
			float invaderY = y * 50 + (GAP * y) + 50;
			InvadersV.emplace_back(sf::Vector2f{ invaderX, invaderY });
		}
	}
	//sets all invaders alive to true and alive invaders to 24
	m_aliveInvaders = 24;
	m_allInvadersAlive = true;
	
}

//returns game over bool
bool InvaderManager::setGameOver()
{
	return iGameOver;
}

//return m_allInvadersAlive
bool InvaderManager::allInvadersAlive()
{
	return m_allInvadersAlive;
}

//tests invaders  position
bool InvaderManager::testInvaderPosition(const Invaders& invader) 
{
	//checks if invaders have reached the bottom of the screen
	if (invader.getPosition().y > 600 - 150) {
		//sets game over is true
		iGameOver = true;
	}
	
	return
		(invader.getPosition().x < 15 && m_isMovingLeft) || //Check invader left
		(invader.getPosition().x + Invaders::WIDTH > 800 - 15 && !m_isMovingLeft); //Check invader right
}

