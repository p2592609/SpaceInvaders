#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Include/Collidable.h"

class Shield : public Collidable
{
public:
	//shields width and height
	constexpr static float WIDTH = 90;
	constexpr static float HEIGHT = 20;

private:
	//variables
	sf::Vector2f m_position;
	bool m_isActive = true;

	//variables for shields sprite and texture
	sf::Vector2f shieldSize;
	sf::Texture shieldTex;
	sf::Sprite shieldSprite;
	static const int iNumFrames = 3;
	int iCurrentFrame = 0;
	sf::IntRect shieldrects[iNumFrames];

public:
	//constructor
	Shield(sf::Vector2f position);

	
	//method to get position
	const sf::Vector2f& getPosition() const;
	//method to get is active
	bool isActive() const;
	//method to draw
	void draw(sf::RenderWindow &window);

	void onCollide(Collidable& other) override;
};