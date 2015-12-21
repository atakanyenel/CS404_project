#include "Agent.h"
using namespace std;
int adj[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
void printMap(Map,int);
void Solve(Agent,Map&);
int main()
{
	int size=4;

	Map Game(size);
	Game[2][3].Breeze=true;
	cout<<Game[2][3].Breeze<<endl<<endl<<endl;
	Agent player(Game,0,0);//agent gets the empty map

	printMap(Game,size);

	Game.CreateWorld();//Create game world

	cout<<endl<<endl;
	printMap(Game,size);
	cout<<endl<<endl;
	printMap(player.GetMap(),size);
	cout<<endl<<endl;
	player.PrintLocal();
	Solve(player,Game);

	system("pause");
	return 0;
}
void printMap(Map m,int size)
{
	for (int r=size-1;r>-1;r--)
	{
		for(int c=0;c<size;c++)
		{
			Cell current=m.World[r][c];
			if(current.Gold)
			{
				cout<<" G ";
			}
			else if(current.Breeze)
			{
				cout<<" B ";
			}

			else if(current.Pit)
			{
				cout<<" P ";
			}
			else if(current.Smell)
			{
				cout<<" S ";
			}
			else if(current.Wumpus)
			{
				cout<<" W ";
			}
			else
			{
				cout<<" - ";
			}
		}
		cout<<endl;
	}
}
void Solve(Agent agent,Map & m)
{
	int startingrow=agent.currentr;
	int startingcol=agent.currentc;


	while(agent.hasGold==false) //Run until Gold is back
	{
		Cell current=agent.getCurrentCell(m); //get the properties of the current Cell from World
		agent.UpdateLocal(current);	//Update the local Map
		agent.PrintLocal();
		if(current.Glitter==true)
		{
			agent.Grab(m);	//This function updates the real world. hasGold returns true
		}
		else
		{
			if(current.Breeze==false && current.Smell==false)//meaning adjacents are safe
			{
				agent.adjacentSafe();	//update the local map
				agent.PrintLocal();
			}
			if(current.Breeze==true)
			{
				agent.CheckPit(adj); //Check adjacent for pits

			}
			if(current.Smell==true)
			{
				agent.CheckWumpus(adj); //Check adjacent for Wumpus
			}

			bool moved=false;
			for(int k=0;k<4 && !moved;k++)		//AGENT TRIES TO MOVE
			{
				int newrow=agent.currentr+adj[k][0];
				int newcol=agent.currentc+adj[k][1];
				Cell nextCell=agent.GetMap()[newrow][newcol];
				if(nextCell.visited==false && nextCell.Safe==true) //Found a new unvisited cell
				{
					agent.setDirection(k);
					agent.Forward(); //Agent MOVED
					moved=true;
				}
			}
			if(!moved) //Agent did not moved try something else
			{
				
			}

		}
	}





}

