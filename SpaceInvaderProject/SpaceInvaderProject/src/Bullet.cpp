#include"Include/Bullet.h"
#include<iostream>

Bullet::Bullet(const sf::Vector2f & position, Direction direction)
	: Collidable(WIDTH, HEIGHT)
	, m_position(position)
	, m_direction(direction)
{

}

//method to draws laser
void Bullet::draw(sf::RenderTarget& target)
{

	sf::RectangleShape shape;
	shape.setSize({WIDTH, HEIGHT });
	shape.setPosition(m_position);
	target.draw(shape);
}
//method to update laser
void Bullet::update()
{
	//moves laser across screen 
	m_position.y += 10 * (float)m_direction;
	//if laser leaves the screen set active false
	if (m_position.y - HEIGHT <= 0 || m_position.y + HEIGHT >= 600)
	{
		m_isActive = false;
	}
	
}

//returns lasers position and size
sf::FloatRect Bullet::getBox()
{

	return
	{
		m_position.x,
		m_position.y,
		WIDTH,
		HEIGHT
	};
}


//method to check if laser collides with a collidable
void Bullet::onCollide(Collidable& other)
{
	//sets laser is active to false
	m_isActive = false;
	std::cout <<  "hit";
}


//returns lasers position
const sf::Vector2f & Bullet::getPosition() const
{
	return m_position;
}

//returns laser is active
bool Bullet::isActive() const
{
	return m_isActive;
}

//returns lasers direction
 Bullet::Direction Bullet::getDirection() const
{
	return m_direction;
}