#pragma once
#include <iostream>
#include "Header.h"
using namespace std;

 

struct Hucre
{
	bool Breeze;
	bool Glitter;
	bool Smell;
	bool Wumpus;
	bool Pit;
	bool Gold;
	bool Safe;
	bool visited;
	int absnowumpus;
	int absnopit;
	bool definetelywumpus;
	Hucre()
	{
		Breeze=false;
		Glitter=false;
		Smell=false;
		Wumpus=false;
		Pit=false;
		Gold=false;
		Safe=false;
		visited=false;
		absnowumpus=false;
		absnopit=false;
		definetelywumpus=false;
	}

};

class Percept
{



public:
	Percept(void);
	Percept(int size);
	Percept(Map m,int size)
	{
		for (int row=0;row<size;row++)
		{
			for(int col=0;col<size;col++)
			{
				if(m.World[row][col].Pit)
				{
					World[abs(col-4)][row].Pit=true;
				}
				if(m.World[row][col].Wumpus)
				{
					World[abs(col-4)][row].Wumpus=true;
				}
				if(m.World[row][col].Gold)
				{
					World[abs(col-4)][row].Gold=true;
				}
			}
		}
			setRules();
	}
	void CreateWorld();
	void setRules();
	Hucre World[5][5];
	Percept operator=(Percept other);
	Hucre * operator[](int a)
	{
		return World[a];
	}
	~Percept(void);
	int size;
	int adj[5][2];
private:
	void setAdjBreeze(int r,int c);
	void setAdjSmell(int r,int c);
	
	
};

