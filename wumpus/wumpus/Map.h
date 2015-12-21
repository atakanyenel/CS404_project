#pragma once
#include <iostream>
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
		Breeze=false;
		Glitter=false;
		Smell=false;
		Wumpus=false;
		Pit=false;
		Gold=false;
		Safe=false;
		visited=false;
	}
	bool isSafe()
	{
		if(Pit || Wumpus)
		{
			return false;
		}
		return true;
	}
};

class Map
{



public:
	Map(void);
	Map(int size);
	void CreateWorld();
	void setRules();
	Cell World[4][4];
	Map operator=(Map other);
	Cell * operator[](int a)
	{
		return World[a];
	}
	~Map(void);
	int size;
	int adj[4][2];
private:
	void setAdjBreeze(int r,int c);
	void setAdjSmell(int r,int c);
	
	
};

