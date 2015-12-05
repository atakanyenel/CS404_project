#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>

using namespace std;



int main()
{
	//-- Create the render Window --//
	sf::RenderWindow window(sf::VideoMode(1024, 700), "Tile Map Test", sf::Style::Close);

	//-- Disable Key Repetition to enable button pressed events. --//
	window.setKeyRepeatEnabled(false);

	//--------------------------//
	//-- Declarations Sections --//






	//--------------------------//

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

		//window.draw();

		window.display();
	}
	return 0;
}