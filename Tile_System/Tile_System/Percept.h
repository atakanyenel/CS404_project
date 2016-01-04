#pragma once
#include <iostream>
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
	}
};

class Percept
{



public:
	Percept(void);
	Percept(int size);
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

