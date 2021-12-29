#pragma once
#include <SFML/Graphics.hpp>

class Collidable
{
public:
	//constructor
	Collidable(float width, float height);
	//method to check collisions
	bool tryCollideWith(Collidable& other);
	//method to get object size
	sf::FloatRect getBox() const;

	//method to get position
	virtual const sf::Vector2f& getPosition() const = 0;
	//method to check if an object has been collided with
	virtual void onCollide(Collidable& other) = 0;

private:
	//variable
	sf::Vector2f m_size;
};