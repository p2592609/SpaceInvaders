#include "Include/Invaders.h"
#include<iostream>

Invaders::Invaders(const sf::Vector2f& initialLocation)
	: Collidable(WIDTH, HEIGHT)
	, m_pos(initialLocation)
	, m_initialPos(initialLocation)
{
	//loads invaders texture
	if (!invaderT.loadFromFile(".\\assets\\images\\Sprite_Assets\\InvaderA_01.png"))
	{
		std::cout << "..." << std::endl;
	}
	
	invaderHitBuffer.loadFromFile(".\\assets\\sounds\\invaderBullet.wav");


	invaderHit.setBuffer(invaderHitBuffer);
}
//returns invader is alive or not
bool Invaders::isAlive() const
{
	return m_isAlive;
}

//moves invader
  void Invaders::move(float x, float y)
    {
        m_pos += {x, y};
    }


  //returns invaders current position
  const sf::Vector2f & Invaders::getPosition() const
  {
	  return m_pos;
  }
  //draws invader
  void Invaders::draw(sf::RenderTarget& target)
  {
	  //sets invaders positon, size and texture
	  sf::RectangleShape shape;
	  shape.setSize({ WIDTH,HEIGHT });
	  shape.setPosition(m_pos);
	  shape.setTexture(&invaderT);
	  target.draw(shape);
  }

  //checks if invader collides with colliable
  void Invaders::onCollide(Collidable& other)
  {
	  //if invader collides with colliable sets invader is alive to false
	  m_isAlive = false;
	  invaderHit.play();
	  std::cout << "invader hit" << std::endl;
  }