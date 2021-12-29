#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include<SFML/Audio.hpp>
#include "Include/Bullet.h"
#include "Include/Collidable.h"

class Player : public Collidable
{
public:
	//Players width and height values
	constexpr static int WIDTH = 44;
	constexpr static int HEIGHT = 32;

private:
	//resets players ship
	void restart();
	//vecttor for laser class
	std::vector<Bullet> Bullets;
	//ship sprite and texture
	sf::Sprite shipS;
	sf::Texture shipT;
	//players is alive variable and lives variable
	bool m_isAlive = true;
	int m_livesLeft = 3;
	//player audio variables
	sf::SoundBuffer shipHitBuffer;
	sf::Sound shipHit;


public:
	//constructor
	Player();
	//player left and right method
	void goLeft();
	void goRight();
	//player draw method
	void draw(sf::RenderWindow &window);
	//method to get players position and lasers firing position
	sf::Vector2f getGunPosition() const;
	const sf::Vector2f& getPosition() const;
	//method for players live and is alive
	int getLives() const;
	bool isAlive() const;
	
	//method to check for collisions with player
	void onCollide(Collidable& other) override;






};