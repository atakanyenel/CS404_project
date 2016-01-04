#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
//#include "Header.h"
#include "Agent.h"
#include <vector>
using namespace std;
int adj[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int gamestate=0;
struct coor{

int row;
int col;

coor(int r,int c)
{
row=r;
col=c;
}
};

void Solve(Agent &,Percept&,vector<coor> &,int &,int &,string &,Map&);
void MovingAgent(Agent ,int &,int &);
void printMap(Percept,int);
void SetPlayerDirection(Agent,string &);
void GrabbingGold(Agent,Map &);
void ReleasingGold(Agent,Map &);
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

	//-- Fonts and other resources --//
	sf::Font mainFont;

	sf::Text breezeText;
	sf::Text smellText;
	sf::Text glimmerText;

	if (!mainFont.loadFromFile("Terminal.ttf"))
	{
	}
	else
	{
		cout << "Loaded the font 'Terminal.ttf'" << endl;
	}

	breezeText.setFont(mainFont);
	smellText.setFont(mainFont);
	glimmerText.setFont(mainFont);

	breezeText.setString("B");
	smellText.setString("S");
	glimmerText.setString("G");

	breezeText.setColor(sf::Color::White);
	smellText.setColor(sf::Color::Green);
	glimmerText.setColor(sf::Color::Yellow);

	//-- Environment Textures --//
	sf::Sprite tileSprite;
	sf::Texture tileTexture;

	sf::Sprite pitSprite;
	sf::Texture pitTexture;

	tileTexture.loadFromFile("Tile.png");
	pitTexture.loadFromFile("Pit.png");

	tileSprite.setTexture(tileTexture);
	pitSprite.setTexture(pitTexture);

	//-- Animation and Sprite variables --//

	//-----------------------//
	//--- Player animations --//
	sf::Sprite playerSprite;
	sf::Texture playerSheet;

	if (!playerSheet.loadFromFile("Agent.png"))
	{}
	else
	{ cout << "Loaded the texture for 'Player'" << endl; }

	playerSprite.setTexture(playerSheet);
	playerSprite.setTextureRect(sf::IntRect(0, 0, 80, 100));
	playerSprite.setOrigin(40, 50);

	//-----------------------//

	//-----------------------//
	//--- Wumpus animations --//
	sf::Sprite wumpusSprite;
	sf::Texture wumpusSheet;
	sf::Clock animationClock;
	if (!wumpusSheet.loadFromFile("Wumpus.png"))
	{
	}
	else
	{ cout << "Loaded the texture for 'Wumpus'" << endl; }

	wumpusSprite.setTexture(wumpusSheet);
	wumpusSprite.setScale(3, 3);
	wumpusSprite.setTextureRect(sf::IntRect(0, 0, 32, 22));

	int wumpusAnimSeq = 0;
	animationClock.restart();

	//-----------------------//
	//--- Gold animations --//
	sf::Sprite goldSprite;
	sf::Texture goldSheet;

	if (!goldSheet.loadFromFile("Gold.png"))
	{
	}
	else
	{ cout << "Loaded the texture for 'Gold'" << endl; }

	goldSprite.setTexture(goldSheet);
	goldSprite.setScale(2, 2);
	goldSprite.setTextureRect(sf::IntRect(0, 0, 18, 20));

	int goldAnimSeq = 0;


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
	string playerDir = "left";
	//-- Main action boolean --//

	
	
		/*****ATAKAN****/
			/*Create the world in percept form*/
	int size=5;
	Percept RealWorld(gameMap,5);
	Agent player(RealWorld,0,0);
	vector<coor> path;
	//RealWorld.CreateWorld();
	printMap(RealWorld,5);
	cout<<endl<<endl<<endl;
	/*****END OF ATAKAN*****/

	
	
	
	
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

				else if (event.key.code == sf::Keyboard::Right)
				{
					playerDir = "right";
				}

				else if (event.key.code == sf::Keyboard::Up)
				{
					playerDir = "up";
				}

				else if (event.key.code == sf::Keyboard::Down)
				{
					playerDir = "down";
				}

				else if (event.key.code == sf::Keyboard::Left)
				{
					playerDir = "left";
				}
			}
		}

		if (animationClock.getElapsedTime() >= sf::milliseconds(150))
		{
			wumpusAnimSeq++;
			goldAnimSeq++;
			if (wumpusAnimSeq > 9)
			{ wumpusAnimSeq = 0; }

			if (goldAnimSeq > 5)
			{ goldAnimSeq = 0; }

			wumpusSprite.setTextureRect(sf::IntRect(wumpusAnimSeq * 32, 0, 32, 22));
			goldSprite.setTextureRect(sf::IntRect(goldAnimSeq * 18, 0, 18, 20));
			animationClock.restart();
		}


		window.clear(sf::Color::Black);

		//-- Render the world here --//
		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
			{
				baseRect.setPosition(i * 100 + 5, j * 100 + 5);
				window.draw(baseRect);
				tileSprite.setPosition(baseRect.getPosition());
				tileSprite.setScale(1.9, 1.9);
				window.draw(tileSprite);

				//-- Render the cell attributes --//

				if (gameMap.World[i][j].Breeze)
				{
					breezeRect.setPosition((i * 100) + 10, (j * 100) + 10);
					//window.draw(breezeRect);

					breezeText.setPosition(breezeRect.getPosition());
					window.draw(breezeText);
				}

				if (gameMap.World[i][j].Smell)
				{
					smellRect.setPosition((i * 100) + 10, (j * 100) + 60);
					//window.draw(smellRect);

					smellText.setPosition(smellRect.getPosition());
					window.draw(smellText);
				}

				if (gameMap.World[i][j].Glitter)
				{
					glitterRect.setPosition((i * 100) + 60, (j * 100) + 10);
					//window.draw(glitterRect);

					glimmerText.setPosition(glitterRect.getPosition().x + 15, glitterRect.getPosition().y);
					if(!player.hasGold)
						window.draw(glimmerText);
				}

				//-- Render the cell objects --//

				if (gameMap.World[i][j].Gold)
				{
					goldRect.setPosition((i * 100) + 25, (j * 100) + 25);
					//window.draw(goldRect);

					goldSprite.setPosition(goldRect.getPosition().x + 5, goldRect.getPosition().y);
					if(!player.hasGold)
					window.draw(goldSprite);
				}

				if (gameMap.World[i][j].Pit)
				{
					pitRect.setPosition((i * 100) + 25, (j * 100) + 25);
					window.draw(pitRect);

					pitSprite.setScale(1.90, 1.90);
					pitSprite.setPosition(pitRect.getPosition().x - 20, pitRect.getPosition().y - 20);
					window.draw(pitSprite);
				}

				if (gameMap.World[i][j].Wumpus)
				{
					wumpusRect.setPosition((i * 100) + 25, (j * 100) + 25);
					//window.draw(wumpusRect);

					wumpusSprite.setPosition(wumpusRect.getPosition().x - 25, wumpusRect.getPosition().y - 20);
					window.draw(wumpusSprite);
				}
			}
		}

		playerRect.setPosition(playerX * 100 + 25, playerY * 100  + 25);
		//window.draw(playerRect);
		playerSprite.setScale(0.6, 0.6);

		if (playerDir == "left" || playerDir == "right")
		{
			playerSprite.setTextureRect(sf::IntRect(0, 0, 80, 100));

			if (playerDir == "right")
			{
				playerSprite.scale(-1, 1);
			}
		}

		else
		{
			if (playerDir == "up")
			{
				playerSprite.setTextureRect(sf::IntRect(0, 100, 80, 100));
			}

			else
			{
				playerSprite.setTextureRect(sf::IntRect(0, 200, 80, 100));
			}
		}
		playerSprite.setPosition(playerRect.getPosition().x + 25, playerRect.getPosition().y + 25);
		window.draw(playerSprite);

		window.display();


		//-- All logic Methods and Player movement goes Here --//
		if (ActionEnabled)
		{
			Solve(player,RealWorld,path,playerX,playerY,playerDir,gameMap);

			ActionEnabled = false;
		}
	}
	return 0;
}


void Solve(Agent& agent,Percept & m,vector<coor>  & path,int & PlayerX,int & PlayerY,string & playerDir,Map & gw)
{
	int startingrow=agent.currentr;
	int startingcol=agent.currentc;

	printMap(m,5);
	if(agent.hasGold==false) //Run until Gold is back
	{
		Hucre current=agent.getCurrentCell(m); //get the properties of the current Cell from World
		agent.UpdateLocal(current);	//Update the local Map		sets Safe and visited True
		agent.PrintLocal();
		if(current.Glitter==true)
		{
			agent.Grab(m);	//This function updates the real world. hasGold returns true
			GrabbingGold(agent,gw);
		}
		else
		{
			if(current.Breeze==false && current.Smell==false)//meaning adjacents are safe
			{
				agent.adjacentSafe();	//update the local map
				agent.PrintLocal();
			}

			if(current.Smell==false)
			{
				agent.nowumpusadjacent(adj);
			}
			if(current.Breeze==false)
			{
				agent.nopitadjacent(adj);
			}
			if(current.Breeze==true)
			{
				agent.CheckPit(adj); //Check adjacent for pits

			}
			if(current.Smell==true)
			{
				agent.CheckWumpus(adj); //Check adjacent for Wumpus
			}

			agent.CheckInconsistent();	//if both pit and wumpus are present neither is true

			bool moved=false;
			for(int k=0;k<4 && !moved;k++)		//AGENT TRIES TO MOVE
			{
				int newrow=agent.currentr+adj[k][0];
				int newcol=agent.currentc+adj[k][1];
				Hucre nextCell=agent.GetPercept()[newrow][newcol];
				if(nextCell.visited==false && nextCell.Safe==true) //Found a new unvisited cell
				{
					agent.setDirection(k);	//setDirection function is dependent on k
					SetPlayerDirection(agent,playerDir);
					path.push_back(*new coor(agent.currentr,agent.currentc));
					
					agent.Forward();
					MovingAgent(agent,PlayerX,PlayerY);
					moved=true;
					
				}
			}
			if(!moved) //Agent did not move try something else
			{
				
				agent.currentr=path.back().row;		//Agent goes one Cell back assuming there are safe unvisited Cells
				agent.currentc=path.back().col;
				path.pop_back();
				MovingAgent(agent,PlayerX,PlayerY);
			}

		}
	}
		
	if (!path.empty() && agent.hasGold) //agent comes back from the road
	{
		agent.currentr=path.back().row;
		agent.currentc=path.back().col;
		path.pop_back();
		MovingAgent(agent,PlayerX,PlayerY);
	}
	if(agent.hasGold && agent.currentr==0 && agent.currentc==0)
	{
	agent.Release(m);
	agent.PrintLocal();
	ReleasingGold(agent,gw);
	gamestate=1;			//Win State
	}
	}
void MovingAgent(Agent a,int& px,int& py)
{
	px=a.currentc;
	py=abs(a.currentr-4);

}

void printMap(Percept m,int size)
{
	for (int r=size-1;r>-1;r--)
	{
		for(int c=0;c<size;c++)
		{
			Hucre current=m.World[r][c];
			if(current.Gold)
			{
				cout<<" G ";
			}
			else if(current.Pit)
			{
				cout<<" P ";
			}
			else if(current.Breeze)
			{
				cout<<" B ";
			}
				else if(current.Wumpus)
			{
				cout<<" W ";
			}
			
			else if(current.Smell)
			{
				cout<<" S ";
			}
		
			else
			{
				cout<<" - ";
			}
		}
		cout<<endl;
	}
}
void SetPlayerDirection(Agent a,string &pdir)
{
	if(a.dir==a.NORTH)
		pdir="up";
	else if(a.dir==a.SOUTH)
	pdir="down";
	else if(a.dir==a.WEST)
		pdir="left";
	else if(a.dir==a.EAST)
		pdir="right";

}
void GrabbingGold(Agent a,Map & m)
{
	m.World[a.currentc][abs(4-a.currentr)].Gold=false;
	m.World[a.currentc][abs(4-a.currentr)].Glitter=false;
	
	
}

void ReleasingGold(Agent a,Map & m)
{
	m.World[a.currentc][abs(4-a.currentr)].Gold=true;
	m.World[a.currentc][abs(4-a.currentr)].Glitter=true;

}