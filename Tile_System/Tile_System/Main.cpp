#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <map>
#include <cmath>
#include "Header.h"

using namespace std;
typedef std::map<int, int>::iterator it_type;

map<int, int> getFringe(int x, int y);


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
	map<int, int> deneme = getFringe(2, 2);
	cout << deneme.size() << endl;

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
	breezeRect.setFillColor(sf::Color::Cyan);
	breezeRect.setSize(sf::Vector2f(25, 25));

	sf::RectangleShape glitterRect;
	glitterRect.setFillColor(sf::Color::Magenta);
	glitterRect.setSize(sf::Vector2f(25, 25));
	

	sf::Color smellColor(165, 42, 42);
	sf::RectangleShape smellRect;
	smellRect.setFillColor(smellColor);
	smellRect.setSize(sf::Vector2f(25, 25));

	//-- Player Rectangle --//

	sf::RectangleShape playerRect;
	playerRect.setFillColor(sf::Color::Red);
	playerRect.setSize(sf::Vector2f(50, 50));

	//-- Player Information --//
	
	int playerX = 4;
	int playerY = 4;

	//-- Main Game Loop --//
	while (window.isOpen())
	{
		Sleep(250);

		//-- Event Methods --//
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			playerY--;
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
	}
	return 0;
}



map<int,int> getFringe(int x, int y){
	map<int,int> f;
	f[x] = y;
	int i = x, j = y;
	while (i - 1 >= 0 && j + 1 <= 4){
		i = i - 1;
		j = j + 1;
		f[i] = j;
	}
	i = x; j = y;
	while (i + 1 <= 4 && j - 1 >= 0){
		i = i + 1;
		j = j - 1;
		f[i] = j;
	}
	return f;
}

void inTheFringeZeros(Map & agentmap, map<int, int> &m){
	typedef std::map<int, int>::iterator it_type;
	for (it_type iterator = m.begin(); iterator != m.end(); iterator++) {
		// iterator->first = key
		// iterator->second = value
		int x = iterator->first;
		int y = iterator->second;
		if ((x - 1 >= 0 && !agentmap.World[x - 1][y].Breeze) || x - 1 < 0){ //Pitler
			if ((y + 1 <= 4 && !agentmap.World[x][y + 1].Breeze) || y + 1 > 4){
				agentmap.World[x][y].Pit = 0;
			}
		}

		if ((x - 1 >= 0 && !agentmap.World[x - 1][y].Glitter) || x - 1 < 0){
			if ((y + 1 <= 4 && !agentmap.World[x][y + 1].Glitter) || y + 1 > 4){
				agentmap.World[x][y].Gold = 0;
			}
		}

		if ((x - 1 >= 0 && !agentmap.World[x - 1][y].Smell) || x - 1 < 0){
			if ((y + 1 <= 4 && !agentmap.World[x][y + 1].Smell) || y + 1 > 4){
				agentmap.World[x][y].Wumpus = 0;
			}
		}
	}
}

int Factorial(int val)
{
	int Result = 1;
	for (int i = 1; i <= val; i++)
	{
		Result *= i;
	}
	return Result;
}
int Combination(int N, int R)
{
	return (Factorial(N)) / ((Factorial(N - R)) * Factorial(R));
}

float probSum(float prior, int n){
	float sum = 0;
	for (int i = 1; i <= n; i++){
		int comb = Combination(n, i);
		sum += comb*pow(prior, i)*pow(1 - prior, n - i);
	}
	return sum;
}

int pitProb(int x, int y, Map &agentmap, float prior){
	map<int, int> fringe = getFringe(x, y);
	inTheFringeZeros(agentmap, fringe);
	if (!agentmap.World[x][y].Pit) return 0;
	int counter = 0, zeroCounter = 0;
	typedef std::map<int, int>::iterator it_type;
	for (it_type iterator = fringe.begin(); iterator != fringe.end(); iterator++) {
		// iterator->first = key
		// iterator->second = value
		counter++;
		int x = iterator->first;
		int y = iterator->second;
		if (!agentmap.World[x][y].Pit) zeroCounter++;
	}
	float positive = prior*probSum(prior, counter - zeroCounter-1);
	float negative = (1 - prior)*probSum(prior, counter - zeroCounter - 1);
	if (x == 0 || y == 4){
		negative -= (1 - prior)*probSum(prior, counter - zeroCounter - 2);
	}

	return positive / (positive + negative);

}

int wumpusProb(int x, int y, Map &agentmap, float prior){
	map<int, int> fringe = getFringe(x, y);
	inTheFringeZeros(agentmap, fringe);
	if (!agentmap.World[x][y].Smell) return 0;
	int counter = 0, zeroCounter = 0;
	typedef std::map<int, int>::iterator it_type;
	for (it_type iterator = fringe.begin(); iterator != fringe.end(); iterator++) {
		// iterator->first = key
		// iterator->second = value
		counter++;
		int x = iterator->first;
		int y = iterator->second;
		if (!agentmap.World[x][y].Wumpus) zeroCounter++;
	}
	float positive = prior*probSum(prior, counter - zeroCounter - 1);
	float negative = (1 - prior)*probSum(prior, counter - zeroCounter - 1);
	if (x == 0 || y == 4){
		negative -= (1 - prior)*probSum(prior, counter - zeroCounter - 2);
	}

	return positive / (positive + negative);

}

int goldProb(int x, int y, Map &agentmap, float prior){
	map<int, int> fringe = getFringe(x, y);
	inTheFringeZeros(agentmap, fringe);
	if (!agentmap.World[x][y].Gold) return 0;
	int counter = 0, zeroCounter = 0;
	typedef std::map<int, int>::iterator it_type;
	for (it_type iterator = fringe.begin(); iterator != fringe.end(); iterator++) {
		// iterator->first = key
		// iterator->second = value
		counter++;
		int x = iterator->first;
		int y = iterator->second;
		if (!agentmap.World[x][y].Gold) zeroCounter++;
	}
	float positive = prior*probSum(prior, counter - zeroCounter - 1);
	float negative = (1 - prior)*probSum(prior, counter - zeroCounter - 1);
	if (x == 0 || y == 4){
		negative -= (1 - prior)*probSum(prior, counter - zeroCounter - 2);
	}

	return positive / (positive + negative);

}