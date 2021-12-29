#include <SFML/Graphics.hpp>
#include <iostream>
#include"Include/Player.h"
#include "Include/InvaderManager.h"
#include"Include/Bullet.h"
#include"Include/Shield.h"

void main()
{
	

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Drawing Window");

	window.setFramerateLimit(60);
	
	//class objects
	InvaderManager e1;
	std::vector<Bullet> Bullets;
	Player p1;
	std::vector<Shield> s1;

	//variables
	sf::Text gameOverLabel;
	sf::Text lives;
	sf::Text livesLabel;
	sf::Text scoreT;
	sf::Text scoreLabel;

	sf::Clock updateClock;
	sf::Time updateTime = sf::seconds(1/60);
	sf::Time DeltaTime;
	sf::Clock shootClock;
	sf::Time shootTime = sf::seconds(1);
	sf::Clock eShootClock;
	sf::Time eShootTime = sf::seconds(2);

	sf::Font uniFont;
	if (!uniFont.loadFromFile(".\\assets\\fonts\\unifont.TTF"));

	sf::Music gameMusic;
	if (!gameMusic.openFromFile(".\\assets\\sounds\\03_Mercury.wav"));

	sf::SoundBuffer invaderBulletBuffer;
	if (!invaderBulletBuffer.loadFromFile(".\\assets\\sounds\\InvaderBullet.wav"));
	sf::SoundBuffer shipBulletBuffer;
	if (!shipBulletBuffer.loadFromFile(".\\assets\\sounds\\ShipBullet.wav"));
	

	sf::Sound invaderBullet;
	invaderBullet.setBuffer(invaderBulletBuffer);
	sf::Sound shipBullet;
	shipBullet.setBuffer(shipBulletBuffer);
	

	int score = 0;
	bool pGameOver = false;
	bool iGameOver = false;

	//text set up
	gameOverLabel.setFont(uniFont);
	gameOverLabel.setString("GAMEOVER");
	gameOverLabel.setCharacterSize(20);
	gameOverLabel.setPosition(350, 300);
	gameOverLabel.setFillColor(sf::Color::White);

	lives.setFont(uniFont);
	lives.setString(std::to_string(p1.getLives()));
	lives.setCharacterSize(20);
	lives.setPosition(760, 20);
	lives.setFillColor(sf::Color::White);

	livesLabel.setFont(uniFont);
	livesLabel.setString("Lives:");
	livesLabel.setCharacterSize(20);
	livesLabel.setPosition(700, 20);
	livesLabel.setFillColor(sf::Color::White);

	scoreT.setFont(uniFont);
	scoreT.setCharacterSize(20);
	scoreT.setPosition(140, 20);
	scoreT.setFillColor(sf::Color::White);

	scoreLabel.setFont(uniFont);
	scoreLabel.setString("Score:");
	scoreLabel.setCharacterSize(20);
	scoreLabel.setPosition(60, 20);
	scoreLabel.setFillColor(sf::Color::White);

	//addeds 3 shields and set their postion
	for (int i = 0; i < 3; i++)
	{


		s1.emplace_back(sf::Vector2f{ ((float)i + 1) * 185, 400 });

	}

	gameMusic.play();

	while (window.isOpen())
	{
		
		if (gameMusic.getStatus() == sf::Music::Stopped) 
		{
			gameMusic.setLoop(true);
		}
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			//input
			if (event.type == sf::Event::KeyPressed)
			{
				//when player presses left arrow key player object calls player class function to move the player left
				if (event.key.code == sf::Keyboard::Left) p1.goLeft();
				//when player presses right arrow key player object calls player class function to move the player right
				if (event.key.code == sf::Keyboard::Right) p1.goRight();
				//when player presses space shoots laser
				if (event.key.code == sf::Keyboard::Space)
				{
					//if statement handles the attack speed of the laser
					if (shootClock.getElapsedTime() > shootTime)
					{
						//gets laser position
						auto point = p1.getGunPosition();
						Bullets.emplace_back(point, Bullet::Direction::up);
						shipBullet.play();
						shootClock.restart();


					}

					
				}
			}
			
		}
		
		//Update loop for game
		if (updateClock.getElapsedTime() > updateTime && !pGameOver && !iGameOver)
		{
			//when invaders die adds invaders back in
			if (!e1.allInvadersAlive())
			{
				e1.addInvaders();
			}

			//moves all invaders
			e1.invaderStep();
			
			//checks if invades collide with lasers
			auto collision = e1.tryCollideWithBullets(Bullets);
			
			//updates score
			score += collision.first;
			//handles invaders laser
			if (eShootClock.getElapsedTime() > eShootTime)
			{
				auto enemyShoot = e1.getRandomLowestInvaderPoint();
				Bullets.emplace_back(enemyShoot, Bullet::Direction::down);
				invaderBullet.play();
				eShootClock.restart();
			}

			for (auto itr = Bullets.begin(); itr != Bullets.end();) {
				auto& proj = *itr;
				if (!proj.isActive()) {
					itr = Bullets.erase(itr);
				}
				else {
					//Test for player getting hit 
					proj.tryCollideWith(p1);

					for (auto& shield : s1)
					{
						//checks if lasers collide with shields
						if (shield.isActive())
						{
							proj.tryCollideWith(shield);
						}
					}
						
						
						
						
					
					//updates laser
					proj.update();
					itr++;
				}
			}

			
			
			
			
			//checks if game is over
			if (p1.getLives() <= 0) pGameOver = true;
			if (e1.setGameOver()) iGameOver = true;

			//gets score and lives value and changes it to string
			scoreT.setString(std::to_string(score));
			lives.setString(std::to_string(p1.getLives()));
			
			updateClock.restart();
		}

		//if game is over display gameover screen
		if(pGameOver || iGameOver)
		{
			window.clear(sf::Color::Black);

			scoreT.setPosition(400, 350);
			scoreLabel.setPosition(340, 350);
			window.draw(scoreT);
			window.draw(scoreLabel);
			
			
			window.draw(gameOverLabel);
			window.display();
		}
		
		//if game is not over draw and display game
		if (!pGameOver && !iGameOver)
		{
			window.clear(sf::Color::Black);

			e1.drawInvaders(window);
			p1.draw(window);
			for (auto& shield : s1)
			{

				if (shield.isActive())
				{
					shield.draw(window);
				}
			}
			for (auto& proj : Bullets)
			{
				proj.draw(window);
			}
			window.draw(lives);
			window.draw(livesLabel);
			window.draw(scoreT);
			window.draw(scoreLabel);
			window.display();


		}
		
	}
}