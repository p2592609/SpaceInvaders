#include"Include/Shield.h"
#include<iostream>

Shield::Shield(sf::Vector2f position)
	: Collidable(WIDTH, HEIGHT)
	, m_position(position)

{

	
	
	

}


//draws shield
void Shield::draw(sf::RenderWindow &window)
{
	//loads shield texture
	if (!shieldTex.loadFromFile(".\\assets\\images\\FullBlockSS.png"))
	{
		std::cout << "..." << std::endl;
	}
	//setting up shield sprite and texture
	sf::Vector2f shieldSize(90, 20);

	shieldrects[0] = sf::IntRect(0, 0, 30, 20);
	shieldrects[1] = sf::IntRect(30, 0, 30, 20);
	shieldrects[2] = sf::IntRect(60, 0, 30, 20);

	shieldSprite.setScale(shieldSize.x / shieldTex.getSize().x * 3.0f, shieldSize.y / shieldTex.getSize().y);
	shieldSprite.setOrigin(shieldSize.x / 2.f / shieldSprite.getScale().x / 2.f, shieldSize.y / 2.f / shieldSprite.getScale().y);
	shieldSprite.setPosition(m_position.x + 15, m_position.y);
	shieldSprite.setTexture(shieldTex);
	shieldSprite.setTextureRect(shieldrects[iCurrentFrame]);
	
	
 window.draw(shieldSprite);
	
}

//when shield collides with collidable 
void Shield::onCollide(Collidable& other)
{
	//changes shields frame 
	iCurrentFrame++;
	//if shield has been hit 3 times set active to false
	if (iCurrentFrame >= iNumFrames) m_isActive = false;
	//changes shields texture
	shieldSprite.setTextureRect(shieldrects[iCurrentFrame]);
	std::cout << "hitShield";
}


//returns shields position
const sf::Vector2f & Shield::getPosition() const
{
	return m_position;
}

//returns shield is active or not
bool Shield::isActive() const
{
	return m_isActive;
}
