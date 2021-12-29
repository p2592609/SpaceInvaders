#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Include/Collidable.h"

class Bullet : public Collidable
{
public:
	//width and height of the laser
	constexpr static float HEIGHT = 24;
	constexpr static float WIDTH = 12;

	//class to check the direction of the laser 
	enum class Direction
	{
		up = -1,
		down = 1
	};
private:
	//variables
	sf::Vector2f m_position;
	Direction m_direction;

	bool m_isActive = true;


public:


	//constructor
	Bullet(const sf::Vector2f& position, Direction direction);
	//method to update laser
	void update();
	//method to get size and position of laser
	sf::FloatRect getBox();
	//method to get laser position
	const sf::Vector2f& getPosition() const;
	//method to get laser direction
	Direction getDirection() const;
	//method to check laser is active
	bool isActive() const;
	
	//draw method
	void draw(sf::RenderTarget& target);

	//method to check for collision
	void onCollide(Collidable& other) override;
	

};