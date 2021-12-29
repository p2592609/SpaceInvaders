#include "Include/Collidable.h"
#include<iostream>

Collidable::Collidable(float width, float height)
	: m_size(width, height)
{}

//returns whether object collides with passed object
bool Collidable::tryCollideWith(Collidable & other)
{
	if (getBox().intersects(other.getBox())) {
		onCollide(other);
		other.onCollide(*this);
		return true;
	}
	return false;
}

//gets objects size and position
sf::FloatRect Collidable::getBox() const
{
	return
	{
		getPosition().x,
		getPosition().y,
		m_size.x,
		m_size.y
	};
}