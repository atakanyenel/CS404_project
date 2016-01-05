#pragma once
#include "Percept.h"
		// NORTH SOUTH EAST WEST 
class Agent
{
		
public:
	Agent(Percept m,int r,int c);
	Percept GetPercept();
	~Agent(void);
	void LeftTurn();
	void RightTurn();
	void Forward();
		enum direction{NORTH,SOUTH,EAST,WEST};
	direction dir;
	void Grab(Percept &);
	void Release(Percept &);
	void Shoot(Percept &);
	void UpdateLocal(Hucre current);
	void adjacentSafe();
	void setDirection(direction);
	void setDirection(int d);
	void PrintLocal();
	void CheckPit(int adj[4][2]);
	void CheckWumpus(int adj[4][2]);
	void CheckInconsistent();
	Hucre getCurrentCell(Percept m);
	void nowumpusadjacent(int adj[4][2]);
	void nopitadjacent(int adj[4][2]);
		bool hasGold;
	void definetelyWumpus(Percept &World);
	bool isStuck();
	int currentc;
		int currentr;
	Percept local;
	bool wumpusfound;
private:
	bool hasarrow;
};

