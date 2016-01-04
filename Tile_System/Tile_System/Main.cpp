#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include "Header.h"

using namespace std;



int main()
{
	//-- Create the render Window --//
	sf::RenderWindow window(sf::VideoMode(500, 500), "Wumpus World", sf::Style::Close);
	window.setFramerateLimit(60);
	//-- Disable Key Repetition to enable button pressed events. --//
	window.setKeyRepeatEnabled(false);

	//--------------------------//
	//-- Declarations Sections --//
	int mapScale = 5;
	Map gameMap;
	gameMap.CreateWorld();

	//-- Stores tile information --//



	//-- Rectangles for representing cell Data --//

	sf::RectangleShape goldRect;
	goldRect.setFillColor(sf::Color::Yellow);
	goldRect.setSize(sf::Vector2f(50, 50));

	sf::RectangleShape wumpusRect;
	wumpusRect.setFillColor(sf::Color::Green);
	wumpusRect.setSize(sf::Vector2f(50, 50));

	sf::RectangleShape pitRect;
	pitRect.setFillColor(sf::Color::Black);
	pitRect.setSize(sf::Vector2f(50, 50));

	sf::RectangleShape baseRect;
	baseRect.setFillColor(sf::Color::Blue);
	baseRect.setSize(sf::Vector2f(90, 90));

	//-- Attribute Rectangles --//

	sf::RectangleShape breezeRect;
	breezeRect.setFillColor(sf::Color::Black);
	breezeRect.setSize(sf::Vector2f(25, 25));

	sf::RectangleShape glitterRect;
	glitterRect.setFillColor(sf::Color::Yellow);
	glitterRect.setSize(sf::Vector2f(25, 25));
	

	sf::Color smellColor(165, 42, 42);
	sf::RectangleShape smellRect;
	smellRect.setFillColor(sf::Color::Green);
	smellRect.setSize(sf::Vector2f(25, 25));

	//-- Player Rectangle --//

	sf::RectangleShape playerRect;
	playerRect.setFillColor(sf::Color::Red);
	playerRect.setSize(sf::Vector2f(50, 50));

	//-- Player Information --//
	
	int playerX = 0;
	int playerY = 4;

	//-- Main action boolean --//

	bool ActionEnabled = false;

	//-- Main Game Loop --//
	while (window.isOpen())
	{
		//-- Event Methods --//
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					ActionEnabled = true;
				}
			}
		}


		window.clear(sf::Color::Black);

		//-- Render the world here --//
		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
			{
				baseRect.setPosition(i * 100 + 5, j * 100 + 5);
				window.draw(baseRect);

				//-- Render the cell attributes --//

				if (gameMap.World[i][j].Breeze)
				{
					breezeRect.setPosition((i * 100) + 10, (j * 100) + 10);
					window.draw(breezeRect);
				}

				if (gameMap.World[i][j].Smell)
				{
					smellRect.setPosition((i * 100) + 10, (j * 100) + 60);
					window.draw(smellRect);
				}

				if (gameMap.World[i][j].Glitter)
				{
					glitterRect.setPosition((i * 100) + 60, (j * 100) + 10);
					window.draw(glitterRect);
				}

				//-- Render the cell objects --//

				if (gameMap.World[i][j].Gold)
				{
					goldRect.setPosition((i * 100) + 25, (j * 100) + 25);
					window.draw(goldRect);
				}

				if (gameMap.World[i][j].Pit)
				{
					pitRect.setPosition((i * 100) + 25, (j * 100) + 25);
					window.draw(pitRect);
				}

				if (gameMap.World[i][j].Wumpus)
				{
					wumpusRect.setPosition((i * 100) + 25, (j * 100) + 25);
					window.draw(wumpusRect);
				}
			}
		}

		playerRect.setPosition(playerX * 100 + 25, playerY * 100  + 25);
		window.draw(playerRect);
		window.display();


		//-- All logic Methods and Player movement goes Here --//
		if (ActionEnabled)
		{
			playerY--;
			playerX++;


			ActionEnabled = false;
		}
	}
	return 0;
}