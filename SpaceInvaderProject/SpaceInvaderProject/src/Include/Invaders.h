#pragma once

#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include "Include/Collidable.h"

class Invaders : public Collidable 
{
public: 
	//invader's width and height values
	constexpr static float WIDTH = 50;
	constexpr static float HEIGHT = 50;

private:
	//invader's start position and current position
	sf::Vector2f m_initialPos;
	sf::Vector2f m_pos;
	
	//invader's sprite and texture
	sf::Sprite invaderS;
	sf::Texture invaderT;

	//invader audio variables
	sf::SoundBuffer invaderHitBuffer;
	sf::Sound invaderHit;

public:
	//constructor
	Invaders(const sf::Vector2f& initialLocation);
	//method for moving invaders
	void move(float x, float y);
	//method to get invader's position
	const sf::Vector2f& getPosition() const;
	//method to check invader is alive and alive variable
	bool isAlive() const;
	bool m_isAlive = true;
	//draw method
	void draw(sf::RenderTarget& target);

	//method to check if the invader collides with a colliable
	void onCollide(Collidable& other) override;
};