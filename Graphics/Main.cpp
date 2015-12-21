#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>

using namespace std;



int main()
{
	//-- Create the render Window --//
	sf::RenderWindow window(sf::VideoMode(500, 500), "Wumpus World", sf::Style::Close);

	//-- Disable Key Repetition to enable button pressed events. --//
	window.setKeyRepeatEnabled(false);

	//--------------------------//
	//-- Declarations Sections --//

	//-- Stores tile information --//
	struct tile
	{
		bool breeze;
		bool smell;
		bool wumpus;
		bool pit;
		
		sf::RectangleShape baseRect;
		sf::RectangleShape tileRect;
	};

	//-- World vector stores world information --//
	vector<vector<tile>> worldVect;


	



	//--------------------------//

	//-- Popuplate the world vector --//

	tile nullTile;
	nullTile.breeze = false;
	nullTile.pit = false;
	nullTile.smell = false;
	nullTile.wumpus = false;

	nullTile.baseRect.setFillColor(sf::Color::Red);
	nullTile.baseRect.setSize(sf::Vector2f(90, 90));

	nullTile.tileRect.setFillColor(sf::Color::Cyan);
	nullTile.tileRect.setSize(sf::Vector2f(70, 70));

	for(int i = 0; i < 5; i++)
	{
		vector<tile> temp;

		for(int j = 0; j < 5; j++)
		{ 
			nullTile.baseRect.setPosition(i*100 + 5,j*100 + 5);
			nullTile.tileRect.setPosition(i*100 + 15,j*100 + 15);
			temp.push_back(nullTile); 
		}

		worldVect.push_back(temp);
	}

	//-- Main Game Loop --//
	while (window.isOpen())
	{
		//-- Event Methods --//
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		window.clear(sf::Color::Black);

		//-- Render the world here --//
		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
			{
				window.draw(worldVect[i][j].baseRect);
				window.draw(worldVect[i][j].tileRect);
			}
		}


		window.display();
	}
	return 0;
}