#include "Agent.h"
#include <vector>
using namespace std;
int adj[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
struct coor{

int row;
int col;

coor(int r,int c)
{
row=r;
col=c;
}
};
//Function prototypes
void printMap(Map,int);
void Solve(Agent,Map&);
int main()
{
	int size=4;

	Map Game(size);
	Agent player(Game,0,0);//agent gets the empty map
	vector<coor> path; //The agent keeps his path in memory
	printMap(Game,size);

	Game.CreateWorld();//Create game world
	
	cout<<endl<<endl;
	printMap(Game,size);
	cout<<endl<<endl;
	printMap(player.GetMap(),size);
	cout<<endl<<endl;
	player.PrintLocal();
	Solve(player,Game,path);

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
void Solve(Agent agent,Map & m,vector<coor>  & path)
{
	int startingrow=agent.currentr;
	int startingcol=agent.currentc;


	while(agent.hasGold==false) //Run until Gold is back
	{
		Cell current=agent.getCurrentCell(m); //get the properties of the current Cell from World
		agent.UpdateLocal(current);	//Update the local Map		sets Safe and visited True
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

			agent.CheckInconsistent();	//if both pit and wumpus are present neither is true

			bool moved=false;
			for(int k=0;k<4 && !moved;k++)		//AGENT TRIES TO MOVE
			{
				int newrow=agent.currentr+adj[k][0];
				int newcol=agent.currentc+adj[k][1];
				Cell nextCell=agent.GetMap()[newrow][newcol];
				if(nextCell.visited==false && nextCell.Safe==true) //Found a new unvisited cell
				{
					agent.setDirection(k);	//setDirection function is dependent on k
					path.push_back(*new coor(agent.currentr,agent.currentc));
					agent.Forward(); //Agent MOVED
					moved=true;
				}
			}
			if(!moved) //Agent did not move try something else
			{
				agent.currentr=path.back().row;		//Agent goes one Cell back assuming there are safe unvisited Cells
				agent.currentc=path.back().col;
				path.pop_back();
			}

		}
	}
		
	while (!path.empty()) //agent comes back from the road
	{
		agent.currentr=path.back().row;
		agent.currentc=path.back().col;
		path.pop_back();
	
	}
	agent.Release(m);
}

