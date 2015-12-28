#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>

using namespace std;

struct Cell
{
	bool Breeze;
	bool Glitter;
	bool Smell;
	bool Wumpus;
	bool Pit;
	bool Gold;
	bool Safe;
	bool visited;

	Cell()
	{
		Breeze = false;
		Glitter = false;
		Smell = false;
		Wumpus = false;
		Pit = false;
		Gold = false;
		Safe = false;
		visited = false;
	}
};

struct Map
{
	Cell World[5][5];
};

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
	 

	//gameMap.CreateWorld();

	//-- Stores tile information --//



	//-- Rectangles for representing cell Data --//

	sf::RectangleShape goldRect;
	goldRect.setFillColor(sf::Color::Yellow);
	goldRect.setSize(sf::Vector2f(50, 50));

	sf::RectangleShape wumpusRect;
	wumpusRect.setFillColor(sf::Color::Green);
	wumpusRect.setSize(sf::Vector2f(25, 25));

	sf::RectangleShape baseRect;
	baseRect.setFillColor(sf::Color::Blue);
	baseRect.setSize(sf::Vector2f(90, 90));


	



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

				}

				if (gameMap.World[i][j].Smell)
				{

				}

				if (gameMap.World[i][j].Glitter)
				{

				}

				//-- Render the cell objects --//

				if (gameMap.World[i][j].Gold)
				{
					goldRect.setPosition((i * 100) + 25, (j * 100) + 25);
					window.draw(goldRect);
				}

				if (gameMap.World[i][j].Pit)
				{

				}

				if (gameMap.World[i][j].Wumpus)
				{

				}
			}
		}


		window.display();
	}
	return 0;
}