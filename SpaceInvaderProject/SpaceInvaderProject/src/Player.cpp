#include"Include/Player.h"
#include<iostream>

Player::Player() 
	: Collidable(WIDTH,HEIGHT)
{
	//loads player textue and sets player sprite
	shipT.loadFromFile(".\\assets\\images\\Sprite_Assets\\Ship.png");
	shipS.setPosition(400, 500);
	shipS.setScale(WIDTH / shipT.getSize().x * 2.f, HEIGHT / shipT.getSize().y * 2.f);
	shipS.setOrigin(WIDTH / 2.f / shipS.getScale().x, HEIGHT / 2.f / shipS.getScale().y);
	shipS.setColor(sf::Color::Green);
	shipS.setTexture(shipT);

	
	shipHitBuffer.loadFromFile(".\\assets\\sounds\\ShipBullet.wav");

	
	shipHit.setBuffer(shipHitBuffer);
}

//restart ship method
void Player::restart()
{
	//checks if player has more lives than zero to see if game is over
	if(m_livesLeft > 0)
	{
		//decrements lives 
		m_livesLeft--;
		//resets ship position
		shipS.setPosition(400, 500);
		//sets player back to alive
		m_isAlive = true;
	}
	else
	{
		std::cout << "dead";
	}
}

//moves player left
void Player::goLeft()
{
	//checks if player is within screen boundaries 
	if (shipS.getPosition().x > 0 + shipS.getGlobalBounds().width / 2)
	{
		//moves player left
		shipS.move(-10.f, 0.f);
	}
}

//moves player right
void Player::goRight()
{
	//checks if player is within screen boundaries 
	if (shipS.getPosition().x < 800 - shipS.getGlobalBounds().width / 2)
	{
		//moves player right
		shipS.move(10.f, 0.f);
	}
}

//returns players positoion
const sf::Vector2f & Player::getPosition() const
{
	return shipS.getPosition();
}

//returns lasers position
sf::Vector2f Player::getGunPosition() const
{
	return
	{
		shipS.getPosition().x,
		shipS.getPosition().y - 25
	};
}

//draws player
void Player::draw(sf::RenderWindow &window)
{
	
	window.draw(shipS);
	
}


//returns players lives
int Player::getLives() const
{
	return m_livesLeft;
}
//returns if player is alive or not
bool Player::isAlive() const
{
	return m_isAlive;
}

//when player colliders with other colliable sets player is alive to false and calls restart function
void Player::onCollide(Collidable& other)
{
	m_isAlive = false;
	shipHit.play();
	restart();
}
